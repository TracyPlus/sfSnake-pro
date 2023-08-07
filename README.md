# sfSnake-pro
Final project for OOP.
## 1 功能实现
### 1.1 程序漏洞修复
* 修改 `GameScreen.cpp` 里面的 `void GameScreen::generateFruit()`：
更改水果随机生成的引擎，修复了在随机生成水果时大概率集中生成在页面中间的水平线上的bug
> ```cpp
> - static std::default_random_engine engine;
> - engine.seed(time(NULL));
> + static std::default_random_engine engine(time(NULL));
> ```
* 修改了 `Snake.cpp` 中的 `Snake::Snake()` ：
将"Sounds/pickup.aiff"转码为"Sounds/pickup.wav"，修复了拾取水果后无音效的bug
> ```c++
> - pickupBuffer_.loadFromFile("Sounds/pickup.aiff");
> + pickupBuffer_.loadFromFile("Sounds/pickup.wav");
> ```
* 修改 `Snake.cpp` 里的 `Snake::Snake()` ：
修改了构造函数初始化表的顺序为`Snake`类中声明的顺序
> ```c++
> - Snake::Snake() : direction_(Direction::Up), hitSelf_(false)
> + Snake::Snake() : hitSelf_(false), direction_(Direction::Up)
> ```
* 修改 `MenuScreen.cpp` 里的 `MenuScreen::MenuScreen()` 和 `GameOverScreen.cpp` 里的 `GameOverScreen::GameOverScreen(std::size_t score)`：
将已弃用的`setColor`方法更改为建议使用的`setFillColor`方法
> ```c++ 
> // MenuScreen.cpp
> - snakeText_.setColor(sf::Color::Green);
> + snakeText_.setFillColor(sf::Color::Green);
> // GameOverScreen.cpp
> - text_.setColor(sf::Color::Red);
> + text_.setFillColor(sf::Color::Red);
> ```

### 1.2 附加功能实现
#### (1) 贪吃蛇的控制
* **方向控制**  
1） 按下w/a/s/d 或者 上/下/左/右键 均可以实现贪吃蛇转向转向。  
2） 鼠标点击控制方向，长按拖拽持续控制方向。
当按下鼠标键时，设置一个方向向量，该方向向量为鼠标所在位置(MousePosition)与蛇头所在位置(SnakePosition)的差值。下一时刻，食蛇按照该向量的方向运动；运动的距离为1个标准单位。  
* **速度控制**  
1） 游戏中按空格键可以加速。  
2） 游戏初始界面可以选择 "简单/一般/困难" 三种模式，不同模式下贪吃蛇的速度不同。  
#### (2) 水果的控制
* **随机生成五种颜色水果**  
  1） 加黑色、棕色、红、蓝色、绿色、共5种水果，其中贪食蛇吃了黑色、棕色水果不增加其长度，红色、蓝色、绿色水果增加的长度分别为3、2、1。  
  2） 系统随机生成上述5种水果，保持黑色和褐色水果所占比例为25%，其他的占75%。  
  3） 利用colorCount数组判断当前页面上黑色、棕色果子总数，若小于总数的25%，用引擎1随机生成黑色或棕色果子，否则用引擎2随机生成红、蓝、绿的某种颜色；果子每次生成时相应colorCount++，被吃掉colorCount--，并据此增加不同长度。  
* **生成大水果**  
1） 在分数达到10后，系统会生成大水果，吃了增加长度为10。  
2） 通过布尔变量 `has_gift` 的值使得只有大水果被吃了之后才会产生下一个大水果。  
3） 大水果和普通水果的生成利用Fruit的重载构造实现，大水果以`shape`内嵌图片的方式生成：
> ```cpp
> void GameScreen::generateGift()
> {
>     ...
>     switch (fruitType(colorEngine)) 
>     {
>         case 0:
>             fruit_.push_back(Fruit(
>                 sf::Vector2f(xPos(engine), yPos(engine)),
>                "assets/image/strawberry.png",
>                 5));
>             has_gift = true;
>             break;
>         ...
>     }
> }
> // 构造函数
>     shape_.setRadius(Game::GlobalVideoMode.width / 32.0f);
>     texture.loadFromFile(imagePath);
>     setOriginMiddle(shape_);
>     shape_.setTexture(&texture, true);
>     shape_.setPosition(position);
> ```
#### (3) 绘制精灵版本的贪吃蛇
* **蛇的绘制**  
1） 蛇由蛇头、蛇身体、蛇关节组成。  
2） 蛇头是参考代码绘制的蛇头图片，身体是半径为 $r$ 的黄色圆形，关节是长乘宽为 $r \times \sqrt{3}r$ 的黑色矩形。  
3） 路径节点用一个 `deque<SnakePathNode>` 存储，每次更新游戏数据的时候，根据前进方向 `direction_` 在头位置插入一个（在加速情况下为多个）路径节点，同时判断尾部节点是否有需要加长的部分，如果需要加长则不删除，否则删除尾部节点。  
4） 每个身体节点由10个路径节点定义，每个关节节点是相邻两个身体节点的中间节点，其法向方向由相邻两个关节的差向量决定。  
* **蛇的碰撞/吃到水果判定**  
1） 当蛇头渲染半径和水果的渲染半径相切的时候，判定为吃到水果，长度相应增加。  
2） 当蛇头渲染半径与60个路径节点以外的路径节点渲染半径相交的时候，判断为死亡。这里的60个路径节点保证了一部分锐角转弯的可能性。  

#### (4) 整体界面的绘制
* **背景更改**   
1） 可以修改背景的颜色为白色、黑色、褐色三种。  
2） 修改方式有两种，既可以在菜单界面手动点击选择，也可以游戏中按 B 切换。  
* **网格绘制**  
1） 网格使用与屏幕长宽相关的条状矩形渲染。  
2） 允许 显示/关闭 网格，网格的颜色可以设置为白色、黑色、褐色三种。  
3） 支持游戏中按 G 切换网格的开启/关闭状态，在开启状态下按 B 切换网格颜色。  
4） 同时也支持菜单界面的选择。  
* **UI设计**  
1） 在现有页面基础上增加游戏暂停、帮助、菜单等页面。  
2） 在键盘控制窗口切换基础上，通过`Button`类实现鼠标点击按钮，控制页面跳转，并可以进行暂停游戏、继续游戏、重新开始、返回等操作。  
3） 在现有页面基础上增加游戏暂停、帮助、菜单等页  
4） 游戏中实时显示分数。  
5） 在参考代码基础上，对标题UI、各类buttonUI做了改动。  
## 2 编译环境说明
- Windows 10
- GCC 13.0.1
- x86_64-w64-mingw32
- SFML 2.5.1
- 全部 static 编译
## 3 参考资料
[1] 贪食蛇。源代码: https://github.com/jhpy1024/sfSnake。  
[2] 贪吃蛇参考。源代码：https://github.com/JingYiJun/sfSnakePro。  
[3] SFML库。源代码: https://github.com/SFML/SFML/tree/2.5.x。  
