
#ifndef SERVICE_LOCATOR_HPP
#define SERVICE_LOCATOR_HPP

#include <memory>
#include <functional>

/*
 * Brief: Exception used by ServiceLocator when requesting unregistered services
 */
class ServiceNotAvailable : public std::exception
{
    const char * what() const throw ()
    {
        return "ServiceNotAvailable";
    }
};

/*
 * Brief: ServiceLocator templated class, provides direct access to registered services.
 *
 *        As it's a templated class, there will be instantiated as many classes as registered services.
 *        Each of those instantiated classes will manage it's own service.
 *
 *        All methods in this class are static, so no need to instantiate objects from this class
 */
template <typename Type>
class ServiceLocator
{
    public:

        /*
         * Brief: Delete contructo to avoid creating instances of this class
         */
        ServiceLocator() = delete;

        /*
         * Brief: Method to register services. It takes as a parameter the function that ServiceLocator will use to retrieve
         *        the service object
         *
         * [in] service_retriever : function that will be called to retrieve the service object
         */
        static void RegisterService(std::function<std::shared_ptr<Type>(void)> service_retriever)
        {
            m_service_retriever = service_retriever;
        }

        /*
         * Brief: Method to remove services.
         */
        static void RemoveService()
        {
            m_service_retriever = nullptr;
        }

        /*
         * Brief: Method to Get the objects of the registered services. It relies on the m_service_retriever function to do
         *        the task, so it's on the clients hands to define how this is performed. For example, clients can decide
         *        to create new objects, pass already created object or implements further logic to decide which object to pass
         *        from a list of objects, etc.
         *
         *        ServiceNotAvailable exception is thrown if the service is not registered
         *
         * [out] service_retriever : pointer to the service object
         */
        static std::shared_ptr<Type> GetService() noexcept (false)
        {
            if(m_service_retriever == nullptr)
            {
                throw ServiceNotAvailable();
            }
            return m_service_retriever();
        }

    private:
        /*
         * Brief: to store the service_retriever function, it's initialise to nullptr
         */
        static std::function<std::shared_ptr<Type>(void)> m_service_retriever;
};

#endif