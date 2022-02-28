
#include <ServiceLocator.hpp>

/* ServiceLocator static data will live in this compilation unit, other files will have to reference this definitions */
template <typename Type>
std::function<std::shared_ptr<Type>(void)> ServiceLocator<Type>::m_service_retriever{nullptr};
