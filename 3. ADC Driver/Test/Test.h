void CleanUp();

void Test_ADC_Init();
void Test_ADC_MultiChannel_DMA_SWTrig_Continuous_LinearStream();
void Test_ADC_MultiChannel_DMA_SWTrig_Continuous_CircularStream();
void Test_ADC_MultiChannel_DMA_SWTrig_Oneshot_Single();

void Test_ADC_MultiChannel_IT_HWTrig_Oneshot_Single();
void Test_ADC_MultiChannel_IT_SWTrig_Continuous_Single();
void Test_ADC_MultiChannel_IT_SWTrig_Continuous_CircularStream();
void Test_ADC_MultiChannel_IT_SWTrig_Continuous_LinearStream();
void Test_ADC_SwQueue();

/* Test result inspection functions (for debugger use) */
typedef struct {
    const char* testName;
    unsigned char passed;
    unsigned long timestamp;
    unsigned long errorCode;
} TestResult_t;

void Test_GetSummary(unsigned long* passCount, unsigned long* failCount, unsigned long* totalTests);
TestResult_t* Test_GetResult(unsigned long index);
unsigned char Test_AllPassed(void);
void RunAllTests(void);

/* Error code definitions for test result debugging */
#define TEST_ERROR_NONE                 0U
#define TEST_ERROR_GENERIC_FAIL         1U
#define TEST_ERROR_INIT_FAILED          2U
#define TEST_ERROR_SETUP_BUFFER_FAILED  3U
#define TEST_ERROR_CONVERSION_TIMEOUT   4U
#define TEST_ERROR_WRONG_STATUS         5U
#define TEST_ERROR_READ_GROUP_FAILED    6U
#define TEST_ERROR_STREAM_INCOMPLETE    7U
#define TEST_ERROR_QUEUE_TIMEOUT        8U
