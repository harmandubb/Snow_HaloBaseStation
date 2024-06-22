#include <zephyr/ztest.h>
#include <src/adc_control.h>

// Test cases: 
//  1. Multiplexer is initialized with one channel and as an input 
//  2. Output pins for controlling the multiplexer are initialized 
//  3. Be able to set the pins to control a certain sensor reading (including starting the ADC reading)
//  4. calculate_pressure_differential 
//  5. callback to alert the system that the ADC is done reading

// Implement number four to ensure to get practice with tests. 

// Initialize the overall variables needed for the testing
// No variables to initialize

static void *calculate_pressure_differential_setup(void);
static void calculate_pressure_differential_before(void *data);
static void calculate_pressure_differential_after(void *data);
static void calculate_pressure_differential_teardown(void *data);

// Suite setup
ZTEST_SUITE(adc_control_tests, NULL, calculate_pressure_differential_setup, calculate_pressure_differential_before, calculate_pressure_differential_after, calculate_pressure_differential_teardown);

// Setup function to initialize the base variables for the specific test 
static void *calculate_pressure_differential_setup(void) {
    // No initial setup is needed
    return NULL;
}

static void calculate_pressure_differential_before(void *data) {
    // No pre-test setup is needed
}

static void calculate_pressure_differential_after(void *data) {
    // No post-test actions are needed
}

// Teardown function deinitializing any variables at the end of each test
static void calculate_pressure_differential_teardown(void *data) {
    // No reset is needed due to no shared variables 
}

// Write the test cases 
ZTEST(adc_control_tests, test_assert) {
    // Implement the actual test logic here
    zassert_equal(calculate_pressure_differential(0, 100), -100, "This test should fail because 1 is not equal to 0");
}
