#pragma once

#include <catch2/catch_test_macros.hpp>

class Service
{
public:
    virtual void Operation() = 0;
};

class ServiceNull final : public Service
{
public:
    void Operation() override
    {
        // Do nothing
    }
};

class ServiceLocator
{
public:
    static void SetService(Service* const service)
    {
        m_Service = (service == nullptr) ? &m_NullService : service;
    }

    static Service* GetService()
    {
        return m_Service;
    }
private:
    static ServiceNull m_NullService;
    static Service* m_Service;
};

ServiceNull ServiceLocator::m_NullService{};
Service* ServiceLocator::m_Service{&m_NullService};

class ServiceImplementation final : public Service
{
public:
    void Operation() override
    {
        ++m_Value;
    }

    uint32_t GetValue() const
    {
        return m_Value;
    }
private:
    uint32_t m_Value{0};
};

TEST_CASE("Service Locator - Unit Tests")
{
    ServiceImplementation service{};
    REQUIRE(service.GetValue() == 0);

    ServiceLocator::GetService()->Operation();
    REQUIRE(service.GetValue() == 0);

    ServiceLocator::SetService(&service);
    ServiceLocator::GetService()->Operation();
    REQUIRE(service.GetValue() == 1);

    ServiceLocator::SetService(nullptr);
    ServiceLocator::GetService()->Operation();
    REQUIRE(service.GetValue() == 1);
}
