# weather
Yet another weather forecast for OpenWeatherMap

## Introduction 介绍
这是一个用Qt5写的天气预报程序
* `weather` 主程序，该部分采用Qt5。
* `weather_config` 配置程序，该部分代码兼容Qt4和Qt5。

## Build 编译
### 获取源代码
```
git clone https://github.com/YeLee/weather.git
```
### 编译weather_config配置前端
```
cd weather_config
qmake （系统默认qmake生成Makefile）
make
wget http://bulk.openweathermap.org/sample/city.list.json.gz （获取OpenWeatherMap城市列表文件）
sh newCityList.sh city.list.json.gz （SQLite3生成数据库文件）
```
### 编译weather主程序前端
```
cd weather
/usr/lib/qt5/bin/qmake （仅限Qt5版qmake）
make
```

## Configure 配置程序
把`weather`主程序、`weather_config`配置前端和`weather_config.db`城市列表数据库拷贝到同一目录下即可。
到[OpenWeatherMap](http://www.openweathermap.org/)去申请一个免费的APPID。
打开`weather_config`，配置程序：
* `Country` 国家代码（ISO 3166 Country codes）
* `City` 城市对应的英文名称
* `City Information` 城市信息，包含城市代码和经纬度，重复名称用下拉列表选择
* `Language` 返回的天气信息语言
* `Temperature` 温度格式，支持华氏、摄氏和开氏
* `Update Frequency` 更新频率（单位为分），即程序间隔多长时间会从服务器获取天气信息
* `AutoCloseWindow` 鼠标不在主窗口内自动关闭主窗体（单位为秒）
* `APPID` OpenWeatherMap APPID
* `Submit` 在程序其目录下生成`weather.ini`并退出（这里没有任何提示）

## Running 运行程序
使用一台联网的计算机打开`weather`，点击托盘菜单的`Show`即可查看天气信息
