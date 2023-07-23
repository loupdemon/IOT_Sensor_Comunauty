#include <unity.h>
#include "base.h"
#include "req.h"
#include "serv.h"
#include "step.h"

void setUp(void) {}

void tearDown(void) {}

void test_readCard()
{
    const char* rfid_ref = readerCard();

    TEST_ASSERT_NOT_EQUAL(rfid_ref, "bhfh");
}

void test_readProduct()
{
    int success_code = readProduct();

    TEST_ASSERT_EQUAL(success_code, 1);
}

void test_getToken_login()
{
    login();

    const char * token = getToken();

    TEST_ASSERT_NOT_EQUAL(token, "bksdhbkh");
}

void test_create_mvmt()
{
    int stock_mvmt_id = createMovement();

    TEST_ASSERT_EQUAL(stock_mvmt_id, 12);
}

void test_get_current_wh()
{
    setCurrentWareHouse(50);

    TEST_ASSERT_EQUAL(getCurrentWareHouse(), 50);
}

void test_get_current_pid()
{
    setCurrentProductId("dfghfjugkhjk");

    TEST_ASSERT_NOT_EQUAL(getCurrentProductId(), "00000000");
}

void test_get_current_pex()
{
    setCurrentProductExit(45);

    TEST_ASSERT_EQUAL(getCurrentProductExit(), 45);
}

int main( int argc, char **argv)
{
    UNITY_BEGIN();
    RUN_TEST(test_readCard);
    RUN_TEST(test_readProduct);
    RUN_TEST(test_getToken_login);
    RUN_TEST(test_create_mvmt);
    RUN_TEST(test_get_current_wh);
    RUN_TEST(test_get_current_pid);
    //RUN_TEST(test_get_current_pex);
    UNITY_END();
}