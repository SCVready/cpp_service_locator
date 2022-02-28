
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <ServiceLocator.hpp>

/* Static variables */
template <typename Type>
extern std::function<std::shared_ptr<Type>(void)> ServiceLocator<Type>::m_service_retriever;

/*
 * Test suite ServiceLocatorSingleServiceTest: one service with 2 implementations
 */
class ServiceLocatorSingleServiceTest : public ::testing::Test
{
    public:
        /* Dumb service and mocks */
        class IDumbService
        {
            public:
                virtual void Execute() = 0;
        };

        class DumbServiceImpl1Mock : public IDumbService
        {
            public:
                MOCK_METHOD(void, Execute, ());
        };

        class DumbServiceImpl2Mock : public IDumbService
        {
            public:
                MOCK_METHOD(void, Execute, ());
        };

        /* Test class contructor */
        ServiceLocatorSingleServiceTest()
        {
            m_mock_1 = std::make_shared<DumbServiceImpl1Mock>();
            m_mock_2 = std::make_shared<DumbServiceImpl2Mock>();
        }

        /* Test case TearDown function */
        void TearDown() override
        {
            ServiceLocator<IDumbService>::RemoveService();
        }

    protected:
        std::shared_ptr<DumbServiceImpl1Mock> m_mock_1;
        std::shared_ptr<DumbServiceImpl2Mock> m_mock_2;
};

/*
 * Brief: Check if an exception is raised if we try to obtain the DumbService without being registered first
 */
TEST_F(ServiceLocatorSingleServiceTest, ServiceNotRegistered)
{
    EXPECT_THROW(ServiceLocator<IDumbService>::GetService()->Execute(), ServiceNotAvailable);
}

/*
 * Brief: Check if an exception is raised if we try to obtain the DumbService after being removed
 */
TEST_F(ServiceLocatorSingleServiceTest, ServiceRemoved)
{
    ServiceLocator<IDumbService>::RegisterService([this](){ 
        return this->m_mock_1;
    });

    ServiceLocator<IDumbService>::RemoveService();

    EXPECT_THROW(ServiceLocator<IDumbService>::GetService()->Execute(), ServiceNotAvailable);
}

/*
 * Brief: Register the implementation 1 of the DumbService into the ServiceLocator. Expect that the Mock from the
 *        implementation 1 is called when the object given by the service locator is used
 */
TEST_F(ServiceLocatorSingleServiceTest, Implementation1Registered)
{
    ServiceLocator<IDumbService>::RegisterService([this](){ 
        return this->m_mock_1;
    });

    EXPECT_CALL(*m_mock_1, Execute());

    ServiceLocator<IDumbService>::GetService()->Execute();
}

/*
 * Brief: Register the implementation 2 of the DumbService into the ServiceLocator. Expect that the Mock from the
 *        implementation 2 is called when the object given by the service locator is used
 */
TEST_F(ServiceLocatorSingleServiceTest, Implementation2Registered)
{
    ServiceLocator<IDumbService>::RegisterService([this](){ 
        return this->m_mock_2;
    });

    EXPECT_CALL(*m_mock_2, Execute());

    ServiceLocator<IDumbService>::GetService()->Execute();
}

/*
 * Test suite ServiceLocatorMultipleServiceTest: 2 different registered services at the same time
 */
class ServiceLocatorMultipleServiceTest : public ::testing::Test
{
    public:
        /* Dumb services and mocks */
        class IDumbServiceA
        {
            public:
                virtual void ExecuteA() = 0;
        };

        class IDumbServiceB
        {
            public:
                virtual void ExecuteB() = 0;
        };

        class DumbServiceAImplMock : public IDumbServiceA
        {
            public:
                MOCK_METHOD(void, ExecuteA, ());
        };

        class DumbServiceBImplMock : public IDumbServiceB
        {
            public:
                MOCK_METHOD(void, ExecuteB, ());
        };

        /* Test class contructor */
        ServiceLocatorMultipleServiceTest()
        {
            m_mock_service_A = std::make_shared<DumbServiceAImplMock>();
            m_mock_service_B = std::make_shared<DumbServiceBImplMock>();
        }

        /* Test case TearDown function */
        void TearDown() override
        {
            ServiceLocator<IDumbServiceA>::RemoveService();
            ServiceLocator<IDumbServiceB>::RemoveService();
        }

    protected:
        std::shared_ptr<DumbServiceAImplMock> m_mock_service_A;
        std::shared_ptr<DumbServiceBImplMock> m_mock_service_B;
};

/*
 * Brief: register 2 services into the service locator
 */
TEST_F(ServiceLocatorMultipleServiceTest, TwoServices)
{
    ServiceLocator<IDumbServiceA>::RegisterService([this](){ 
        return this->m_mock_service_A;
    });

    ServiceLocator<IDumbServiceB>::RegisterService([this](){ 
        return this->m_mock_service_B;
    });

    EXPECT_CALL(*m_mock_service_A, ExecuteA());

    ServiceLocator<IDumbServiceA>::GetService()->ExecuteA();

    EXPECT_CALL(*m_mock_service_B, ExecuteB());

    ServiceLocator<IDumbServiceB>::GetService()->ExecuteB();
}
