# Commodity Auction System - Documentation

🤩[upd]click [here](https://ap-cap.vercel.app/) to have an instant preview! 

# 商品竞拍平台-用户手册

## 用户功能

### 用户注册

按照要求依次输入`用户名`,`密码`, `电话号码`, `地址`.系统会自动判断用户名是否已经被注册, 也会基于**regex**判断各项的输入是否符合要求, 不合法的输入将会失败.

<img src="https://yunzinan-pic-bed.oss-cn-nanjing.aliyuncs.com/2022/10/image-20221016094602025.png" alt="image-20221016094602025" style="zoom:40%;" />



<img src="https://yunzinan-pic-bed.oss-cn-nanjing.aliyuncs.com/2022/10/image-20221016094353277.png" alt="image-20221016094353277" style="zoom:33%;" />

<img src="https://yunzinan-pic-bed.oss-cn-nanjing.aliyuncs.com/2022/10/image-20221016094641925.png" alt="image-20221016094641925" style="zoom:33%;" />



### 用户登录

输入用户名和密码, 系统根据已有的注册用户信息, 判定是否登录成功.

<img src="https://yunzinan-pic-bed.oss-cn-nanjing.aliyuncs.com/2022/10/image-20221016094834819.png" alt="image-20221016094834819" style="zoom:33%;" />





<img src="https://yunzinan-pic-bed.oss-cn-nanjing.aliyuncs.com/2022/10/image-20221016095110743.png" alt="image-20221016095110743" style="zoom:33%;" />



### 卖家功能

#### 我的商品: 查看/搜索/修改商品

- 直接点击搜索, 可以查看所有属于该用户发布的商品.

<img src="https://yunzinan-pic-bed.oss-cn-nanjing.aliyuncs.com/2022/10/image-20221016095300489.png" alt="image-20221016095300489" style="zoom:33%;" /> 

<img src="https://yunzinan-pic-bed.oss-cn-nanjing.aliyuncs.com/2022/10/image-20221016095730272.png" alt="image-20221016095730272" style="zoom:33%;" />



- 在搜索框中输入`商品关键词(只需要商品中包含该词)`或`商品ID`, 则会筛选符合的商品显示.

  <img src="https://yunzinan-pic-bed.oss-cn-nanjing.aliyuncs.com/2022/10/image-20221016095925157.png" alt="image-20221016095925157" style="zoom:33%;" />

- 双击某一行的商品, 会弹出该商品的详细信息, 进行查看或修改, 点击确认进行修改,或点击取消撤销本次修改.

<img src="https://yunzinan-pic-bed.oss-cn-nanjing.aliyuncs.com/2022/10/image-20221016100033313.png" alt="image-20221016100033313" style="zoom:33%;" />

<img src="https://yunzinan-pic-bed.oss-cn-nanjing.aliyuncs.com/2022/10/image-20221016100211223.png" alt="image-20221016100211223" style="zoom:33%;" />

#### 订单列表: 查看订单

单击订单列表, 会切换到订单界面, 同时发起一次查看我的订单的请求, 如果未查询到我的订单信息, 会进行提示.

<img src="https://yunzinan-pic-bed.oss-cn-nanjing.aliyuncs.com/2022/10/image-20221016100338746.png" alt="image-20221016100338746" style="zoom:33%;" />

#### 商品发布

按照要求填写后点击确认添加即可发布商品.同样,不合法的输入将会失败.

<img src="https://yunzinan-pic-bed.oss-cn-nanjing.aliyuncs.com/2022/10/image-20221016095524820.png" alt="image-20221016095524820" style="zoom:33%;" />

### 买家功能

#### 商品市场: 查看/竞拍商品

查看逻辑同[卖家界面](#我的商品: 查看/搜索/修改商品).只会显示上架的商品.

- 单击某一个栏目可以进行升序或降序排列
- 双击某一个商品会跳出`竞拍界面`

<img src="https://yunzinan-pic-bed.oss-cn-nanjing.aliyuncs.com/2022/10/image-20221016100906821.png" alt="image-20221016100906821" style="zoom:33%;" />

- 竞拍界面可以查看该商品的详细信息, 并进行出价竞拍.

  <img src="https://yunzinan-pic-bed.oss-cn-nanjing.aliyuncs.com/2022/10/image-20221016101047633.png" alt="image-20221016101047633" style="zoom:33%;" />

> 当然, 系统会对竞拍的状态进行判断:
>
> - 若出价超过当前买家的余额, 会失败.
>
>   <img src="https://yunzinan-pic-bed.oss-cn-nanjing.aliyuncs.com/2022/10/image-20221016101156721.png" alt="image-20221016101156721" style="zoom:25%;" />
>
> - 若出价低于起拍价(底价), 会失败
>
>   <img src="https://yunzinan-pic-bed.oss-cn-nanjing.aliyuncs.com/2022/10/image-20221016101259857.png" alt="image-20221016101259857" style="zoom:33%;" />
>
> - 若已经对该商品出价过, 会失败
>
>   <img src="https://yunzinan-pic-bed.oss-cn-nanjing.aliyuncs.com/2022/10/image-20221016101413478.png" alt="image-20221016101413478" style="zoom:33%;" />
>
> - 成功界面:
>
>   <img src="https://yunzinan-pic-bed.oss-cn-nanjing.aliyuncs.com/2022/10/image-20221016101348291.png" alt="image-20221016101348291" style="zoom:33%;" />

#### 我的订单

出价后, 进入我的订单界面,会显示历史订单.

<img src="https://yunzinan-pic-bed.oss-cn-nanjing.aliyuncs.com/2022/10/image-20221016101538888.png" alt="image-20221016101538888" style="zoom:33%;" />

### 账号中心

账号中心界面显示该用户的所有信息, 可对除用户ID外的信息进行修改.

在输入框中输入新的信息后, 会进行判定, 同样的, 不合法的输入将会失败. 输入完成后, 点击右侧的修改按钮即可修改.

![image-20221016101721885](https://yunzinan-pic-bed.oss-cn-nanjing.aliyuncs.com/2022/10/image-20221016101721885.png)

对于用户余额充值功能, 该栏左侧显示当前余额, 右侧输入一个大于零的整数或一位小数后, 点击充值进行充值.

![image-20221016102035160](https://yunzinan-pic-bed.oss-cn-nanjing.aliyuncs.com/2022/10/image-20221016102035160.png)

## 管理员功能

### 管理员登录

输入管理员账号*admin*, 密码*root*, 点击登录进入管理员界面.

<img src="https://yunzinan-pic-bed.oss-cn-nanjing.aliyuncs.com/2022/10/image-20221016102240369.png" alt="image-20221016102240369" style="zoom:33%;" />

### 商品列表

- 查看/搜索逻辑同卖家和买家界面, 在此不赘述.双击可以查看全部信息并进行修改.

  ![image-20221016102351898](https://yunzinan-pic-bed.oss-cn-nanjing.aliyuncs.com/2022/10/image-20221016102351898.png)

### 用户界面

用户界面显示所有用户的信息, 双击某一用户的状态栏可进行封禁/激活.

![image-20221016102626077](https://yunzinan-pic-bed.oss-cn-nanjing.aliyuncs.com/2022/10/image-20221016102626077.png)

相应的, 被封禁的用户将登录失败.

<img src="https://yunzinan-pic-bed.oss-cn-nanjing.aliyuncs.com/2022/10/image-20221016102748142.png" alt="image-20221016102748142" style="zoom:33%;" />

### 订单列表

使用逻辑同卖家界面和买家界面, 不赘述.

<img src="https://yunzinan-pic-bed.oss-cn-nanjing.aliyuncs.com/2022/10/image-20221016102838016.png" alt="image-20221016102838016" style="zoom:33%;" />

### 终止拍卖

管理员随时可以点击终止拍卖按钮, 系统将判断所有`inProcess`的订单的最终结果(`succeeded/failed`)并显示

![image-20221016102926631](https://yunzinan-pic-bed.oss-cn-nanjing.aliyuncs.com/2022/10/image-20221016102926631.png)

<img src="https://yunzinan-pic-bed.oss-cn-nanjing.aliyuncs.com/2022/10/image-20221016114705749.png" alt="image-20221016114705749" style="zoom:33%;" />

拍卖结束后, 会自动更新订单, 商品, 用户余额信息.

![image-20221016114807417](https://yunzinan-pic-bed.oss-cn-nanjing.aliyuncs.com/2022/10/image-20221016114807417.png)

<img src="https://yunzinan-pic-bed.oss-cn-nanjing.aliyuncs.com/2022/10/image-20221016114859440.png" alt="image-20221016114859440" style="zoom:33%;" />

<img src="https://yunzinan-pic-bed.oss-cn-nanjing.aliyuncs.com/2022/10/image-20221016114920777.png" alt="image-20221016114920777" style="zoom:33%;" />

## 特性-拓展功能

### 基于`MD5加密`的用户密码加密存储

用户密码通过加密存储, 防止密码泄露.

![image-20221016115331383](https://yunzinan-pic-bed.oss-cn-nanjing.aliyuncs.com/2022/10/image-20221016115331383.png)

### 基于`regex`的输入合法性判断和模糊搜索

- 对所有输入框的输入进行限制, 不合法的字符将直接无法输入, 增强了鲁棒性.
- 支持模糊搜索, 增强了搜索功能.

### 基于`Qt`的交互界面和交互逻辑

- 中文显示

- GUI界面, 更加美观

- 简化用户操作逻辑:

  - 买家/卖家界面快速切换

  - 查看/搜索合二为一

  - 查看详细/修改or竞拍合二为一

    
