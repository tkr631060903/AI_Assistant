#include "Application.h"

/* Public variables-----------------------------------------------------------*/
// Application_t Application =
// {
//     Application_main,
//     Application_Error_Handler,
//     Application_Assert_Failed
// };

/* Private function prototypes------------------------------------------------*/

/*
    * @name   Run
    * @brief  系统运行
    * @param  None
    * @retval None
*/
void Application_main()
{
    while (1)
    {
        HAL_Delay(1000);
    }
}

/*
    * @name   Error_Handler
    * @brief  错误处理
    * @param  None
    * @retval None
*/
void Application_Error_Handler()
{
    /* User can add his own implementation to report the HAL error return state */
    printf("Error_Handler");
}

/*
    * @name   Assert_Failed
    * @brief  函数参数错误厝里
    * @param  None
    * @retval None
*/
void Application_Assert_Failed()
{
    /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
}
