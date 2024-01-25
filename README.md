## 推箱子

### 实现方式
* 用QPainter绘画实现游戏画面显示和更新
* gamerole类和gamemap类分别代表游戏角色和游戏地图，它们都有一个公有函数用于绘画自己
* game类需要传入关卡资源文件路径，然后整合上述两个类进行游戏画面显示和监听键盘以及判赢操作
* levelselect类用于显示选择关卡页
* mainMenu类用于显示主界面
* widget类用于主菜单-关卡选择-游戏之间的切换（QStackedWidget实现）

### 其它
* GameMap目录下存放地图文件和通关数据（data.txt），其中data.txt中LevelCnt代表关卡数量，passLevel表示已经通关的关卡数量
* 背景图片来源：https://www.pixiv.net/artworks/113012267
