# Service Locator Pattern

This pattern was inspired by [Game Programming Patterns](https://gameprogrammingpatterns.com/service-locator.html).

## When To Use

This pattern works well paired with the [Singleton pattern](https://github.com/RichardLions/singleton-pattern). Although this pattern improves upon a pure Singleton pattern by creating an abstraction to improve testability, easily switch implementations and additional options to manage service lifetime it should be used when no practical alternatives are available. For example in most situations standard dependency injection through a constructor should be preferred to clearing define dependencies.

However an alternative Service Locator implementation could be to abstract the Service Locator as well and pass that through dependency injection. This would be useful for when the service itself may change at runtime and cannot be cached. Accessing the service via an abstract Service Locator would solve this problem while also strongly defining dependencies.

### Implementation Considerations

This patterns implementation is flexible based on what requirements need to be satisfied. A few examples are:
* Service lifetime and service registration could be controlled by a factory.
* The Locator could also be abstract and used via dependency injection.
* Several services could be stored within the Locator and returned based on a query.
* The use of a null service could be used to log warnings or implemented directly within the Locator.

## Example

Setting and using a service:

```cpp
class Service
{
public:
    virtual void Operation() = 0;
};

class ServiceNull final : public Service
{
public:
    void Operation() override {}
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
        ...
    }
};

{
    ServiceLocator::GetService()->Operation(); // Calls null service

    ServiceLocator::SetService(CreateServiceImplementation());
    ServiceLocator::GetService()->Operation(); // Calls ServiceImplementation
}
```

## Setup

This repository uses the .sln/.proj files created by Visual Studio 2022 Community Edition.
Using MSVC compiler, Preview version(C++23 Preview). 

### Catch2
The examples for how to use the pattern are written as Unit Tests.

Launching the program in Debug or Release will run the Unit Tests.

Alternative:
Installing the Test Adapter for Catch2 Visual Studio extension enables running the Unit Tests via the Test Explorer Window. Setup the Test Explorer to use the project's .runsettings file.

### vcpkg
This repository uses vcpkg in manifest mode for it's dependencies. To interact with vcpkg, open a Developer PowerShell (View -> Terminal).

To setup vcpkg, install it via the Visual Studio installer. To enable/disable it run these commands from the Developer PowerShell:
```
vcpkg integrate install
vcpkg integrate remove
```

To add additional dependencies run:
```
vcpkg add port [dependency name]
```

To update the version of a dependency modify the overrides section of vcpkg.json. 

To create a clean vcpkg.json and vcpkg-configuration.json file run:
```
vcpkg new --application
```

### TODO
- [x] Implementation
- [x] Unit Tests
