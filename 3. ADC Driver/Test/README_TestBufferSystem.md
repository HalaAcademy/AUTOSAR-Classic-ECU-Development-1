# ADC Test Buffer System Documentation

## Overview
The ADC test suite has been designed to operate completely silently without any printf or LED output. All test results are stored in a buffer that can be inspected through a debugger.

## Buffer Structure

### TestResults Array
- **Type**: `TestResult_t TestResults[MAX_TEST_RESULTS]`
- **Size**: 16 test results maximum
- **Location**: Global variable in Test.c

### TestResult_t Structure
```c
typedef struct {
    const char* testName;    // Name of the test function
    boolean passed;          // TRUE if test passed, FALSE if failed
    uint32 timestamp;        // Test execution timestamp (conversion count)
    uint32 errorCode;        // Error code: 0 = pass, 1 = fail, custom codes possible
} TestResult_t;
```

### Global Counters
- `TestPassCount`: Total number of tests that passed
- `TestFailCount`: Total number of tests that failed  
- `TestResultIndex`: Current index in TestResults array

## How to Inspect Test Results

### Using Debugger
1. Set a breakpoint after `RunAllTests()` completes
2. Inspect the following variables:
   - `TestResults[]` - Array of all test results
   - `TestPassCount` - Number of passed tests
   - `TestFailCount` - Number of failed tests
   - `TestResultIndex` - Total number of tests run

### Using Utility Functions
The following functions can be called from debugger or added to your code:

```c
// Get test summary
uint32 passCount, failCount, totalTests;
Test_GetSummary(&passCount, &failCount, &totalTests);

// Get specific test result
TestResult_t* result = Test_GetResult(0); // Get first test result

// Check if all tests passed
boolean allPassed = Test_AllPassed();
```

## Test Functions Included

1. **Test_ADC_Init** - ADC initialization test
2. **Test_ADC_MultiChannel_DMA_SWTrig_Continuous_LinearStream** - DMA with linear buffer
3. **Test_ADC_MultiChannel_DMA_SWTrig_Continuous_CircularStream** - DMA with circular buffer
4. **Test_ADC_MultiChannel_DMA_SWTrig_Oneshot_Single** - DMA oneshot conversion
5. **Test_ADC_MultiChannel_IT_HWTrig_Oneshot_Single** - Hardware trigger test (simulated)
6. **Test_ADC_MultiChannel_IT_SWTrig_Continuous_Single** - Interrupt-based continuous
7. **Test_ADC_MultiChannel_IT_SWTrig_Continuous_CircularStream** - Interrupt circular stream
8. **Test_ADC_MultiChannel_IT_SWTrig_Continuous_LinearStream** - Interrupt linear stream
9. **Test_ADC_SwQueue** - Software queue functionality test

## Example Debugger Session

### Step 1: Run Tests
```c
RunAllTests();  // Set breakpoint after this line
```

### Step 2: Inspect Results
In debugger watch window, add:
- `TestResults` - See all test results
- `TestPassCount` - See pass count
- `TestFailCount` - See fail count

### Step 3: Detailed Analysis
For each test result:
- `TestResults[0].testName` - "ADC_Init"
- `TestResults[0].passed` - TRUE/FALSE
- `TestResults[0].timestamp` - When test ran
- `TestResults[0].errorCode` - Error details

## Test Data Buffers

### Conversion Result Buffers
- `TestBuffer_Single[8]` - Single conversion results
- `TestBuffer_Linear[80]` - Linear stream results (8 channels × 10)
- `TestBuffer_Circular[40]` - Circular stream results (8 channels × 5)

These buffers contain actual ADC conversion values and can be inspected to verify ADC functionality.

## Error Codes
- `0` - Test passed successfully
- `1` - Test failed (generic failure)
- Custom error codes can be added for specific failure types

## Memory Usage
- TestResults array: 16 × 16 bytes = 256 bytes
- Test buffers: ~500 bytes total
- Total: < 1KB of RAM usage

## Integration Notes
- No external dependencies
- No stdio.h required
- Compatible with all embedded debuggers
- Works with JTAG, SWD, and other debug interfaces
