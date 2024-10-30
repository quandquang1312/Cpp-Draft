## CPP Practice

### 1. Callback passing
- Testing the callback function passing from class A to class B.
- The lambda callback function created in A and pass to B
- B will use it whenever neccessary

So B will depends on A (Because B has to have the callback function which is sent by A, so B init after A init)
```
cd callback
```

### 2. EventBus Design Pattern
EventBus design pattern is a design pattern where we want to send data over the classes but do not want the classes
to have other classes' instance. The purpose of it is to reduce the complexity where we have many classes.
For example:

```
Class A;
class B {
    A *a;
};
```

Instead we will have EventBus protocol. Each class will have to Subscribe for the topics. Once a component submit a change,
it will Publish it, the Subscribers will receive it.

```
cd EventBus
```


