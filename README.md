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
* GameMap目录存放地图文件，地图大小固定为10x10，文件命名方法为（以第一关为例）：1.txt，文件第一行表示角色初始位置，后10行表示地图，其中数字0代表空地，1代表围墙，2代表箱子（未进点），3代表箱子（已进点），4代表目标点。
* 如要自定义地图，先在GameMap目录下添加地图文件（命名规则严格遵循数字递增加1，格式参考已有文件），然后将data.txt文件的LevelCnt数值加1
* GameMap文件夹需要和可执行文件处于同级目录下
* 背景图片来源：https://www.pixiv.net/artworks/113012267
