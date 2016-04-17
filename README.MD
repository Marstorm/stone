#Marstone
It is a basic rpc model.
I want Marstone a flexible rpc frame.Just like lots of stones can build varied building.


##require:
>protobuf 

#这个项目还在构思、设想中。

平凡的石头，然后通过加工、重新组建可以构造出各式各样的物件。
我的项目就是想设计一个这样的石头Marstone。
类似于商品，这一过程分为采集、运输、加工、消费。
采集相当于一个系统的输入过程。该过程需要将stone（指定结构的数据）封装成字节流。
运输过程将采集的数据分发给不同的加工组件。
加工需要将字节流解封为指定结构的数据，然后进行运算在封装传出。
消费为最后的环节，将最终的结果返回给用户。