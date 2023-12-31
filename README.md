# AI_Assistant
基于STM32F103开发AI助手

## 设备功能

- WIFI访问服务器ChatGPT
- 播放音乐，播放视频
- 液晶显示屏
- 外扩SD卡储存音频视频等文件(文件系统)
- 智能问答
- 屏幕UI
- ~~模拟USB~~
- 远程升级
- 语音唤醒设备
- 长时间没有触发唤醒词，没有对话自动休眠
- 语音声纹录入

## 上位机/服务器功能

- 音频转文字，文字转音频
- 本地ChatGPT部署
- UART通信
- WIFI/ETH通信
- GPT4，GPT3.5，本地GPT分级访问
- 个人智能AI助手GPT模型训练
- 内置多种训练完成的GPT模型

## 程序功能

- TIM6做定时器
- UART1做调试串口
- 2Kb I2C1 EEPROM
- 8MB SPI1 FLASH
- 三色呼吸灯
- SDIO SD卡
- SD卡支持FatFs
- FreeRTOS
- bootloader
- 模拟USB
- 低功耗模式
- 外部唤醒
