/******************************************************************************

 @file  

 @brief 

 Group: 
 Target Device: 

 ******************************************************************************
 

 ******************************************************************************
 Release Name: 
 Release Date: 2016-06-09 06:57:09
 *****************************************************************************/
#include "Common.h"
#include "Function_Define.h"
#include "N76E003.h"
#include "SFR_Macro.h"
#include "spl_config.h"
#include "spl_gpio.h"
#include "spl_uart.h"
#include "spl_mcu.h"

#include "bufmgr.h"

#if SPL_UART0_EN > 0
extern void SPL_UART0_CALLBACK( uint8_t event );
#endif

#if SPL_UART1_EN > 0
extern void SPL_UART1_CALLBACK( uint8_t event );
#endif

#if SPL_UART0_EN > 0
static FIFO_BUF_t uart0_rx_fifo;
//static FIFO_BUF_t uart0_tx_fifo;
static uint8_t uart0_rx_cache[SPL_UART0_RX_CACHE_SIZE];
//static uint8_t uart0_tx_cache[SPL_UART0_TX_CACHE_SIZE];
#endif

#if SPL_UART1_EN > 0
static FIFO_BUF_t uart1_rx_fifo;
//static FIFO_BUF_t uart1_tx_fifo;
static uint8_t uart1_rx_cache[SPL_UART1_RX_CACHE_SIZE];
//static uint8_t uart1_tx_cache[SPL_UART1_TX_CACHE_SIZE];
#endif

extern void     spl_uart_init      ( uint8_t port )
{
    if( port == SPL_UART_PORT_0 )
    {
        uart0_rx_fifo.buf = uart0_rx_cache;
        uart0_rx_fifo.head = 0;
        uart0_rx_fifo.tail = 0;
        uart0_rx_fifo.size = sizeof( uart0_rx_cache );
        //uart0_tx_fifo.buf = uart0_tx_cache;
        //uart0_tx_fifo.head = 0;
        //uart0_tx_fifo.tail = 0;
        //uart0_tx_fifo.size = sizeof( uart0_tx_cache );
        
        SPL_GPIO_SET_MODE_P06_QUASI();         //Setting UART pin as Quasi mode for transmit
        SPL_GPIO_SET_MODE_P07_QUASI();         //Setting UART pin as Quasi mode for transmit    
        
        SCON = 0x50;            //UART0 Mode1,REN=1,TI=1
        set_SMOD;               //UART0 Double Rate Enable
        T3CON &= 0xF8;          //T3PS2=0,T3PS1=0,T3PS0=0(Prescale=1)
        set_BRCK;               //UART0 baud rate clock source = Timer3

#ifdef FSYS_160000
        RH3    = HIBYTE(65536 - (1000000/SPL_UART0_BAUDRATE)-1);           /*16 MHz */
        RL3    = LOBYTE(65536 - (1000000/SPL_UART0_BAUDRATE)-1);           /*16 MHz */
#endif
#ifdef FSYS_166000
        RH3    = HIBYTE(65536 - (1037500/SPL_UART0_BAUDRATE)-1);           /*16.6 MHz */
        RL3    = LOBYTE(65536 - (1037500/SPL_UART0_BAUDRATE)-1);           /*16.6 MHz */
#endif
#ifdef FSYS_1700kHz
        RH3    = HIBYTE(65536 - (106250/SPL_UART0_BAUDRATE)-1);            /*1.7 MHz */
        RL3    = LOBYTE(65536 - (106250/SPL_UART0_BAUDRATE)-1);            /*1.7 MHz */
#endif
#ifdef FSYS_170000
        RH3    = HIBYTE(65536 - (1062500/SPL_UART0_BAUDRATE)-1);           /*17 MHz */
        RL3    = LOBYTE(65536 - (1062500/SPL_UART0_BAUDRATE)-1);           /*17 MHz */
#endif
        return;
    }
    
    
}

extern void spl_uart_open ( uint8_t port )
{
    if( port == SPL_UART_PORT_0 )
    {
        set_TR3;            //Trigger Timer3
        set_TI;             //For printf function must setting TI = 1
        set_ES;             //enable interrupt
        return;
    }
}

extern void spl_uart_txd( uint8_t port, uint8_t byte )
{
    if( port == SPL_UART_PORT_0 )
    {
        SBUF = byte;
        while(!TI);
        TI = 0;
        set_ES;
    }
}

extern uint8_t  spl_uart_rxd      ( uint8_t port )
{
    uint8_t u8tmp;
    
#if SPL_UART0_EN > 0
    if( port == SPL_UART_PORT_0 )
    {
        spl_mcu_disable_irq();
        u8tmp = fifo_buf_get(&uart0_rx_fifo);
        spl_mcu_enable_irq();
        return u8tmp;
    }
#endif

#if SPL_UART1_EN > 0
    if( port == SPL_UART_PORT_1 )
    {
        spl_mcu_disable_irq();
        u8tmp = fifo_buf_get(&uart1_rx_fifo);
        spl_mcu_enable_irq();
        return u8tmp;
    }
#endif

    return 0;

}

extern uint8_t  spl_uart_txd_full  ( uint8_t port )
{
    //pending mode, never full
    port = port;
    return 0;
}

extern uint8_t  spl_uart_rxd_empty ( uint8_t port )
{
    uint8_t u8tmp;
#if SPL_UART0_EN > 0
    if( port == SPL_UART_PORT_0 )
    {
        spl_mcu_disable_irq();
        u8tmp = fifo_buf_empty(&uart0_rx_fifo);
        spl_mcu_enable_irq();
        return u8tmp;
    }
#endif

#if SPL_UART1_EN > 0
    if( port == SPL_UART_PORT_1 )
    {
        spl_mcu_disable_irq();
        u8tmp = fifo_buf_empty(&uart1_rx_fifo);
        spl_mcu_enable_irq();
        return u8tmp;
    }
#endif

    return 0;
}

extern void spl_uart_close( uint8_t port )
{
#if SPL_UART0_EN > 0
    if( port == SPL_UART_PORT_0 )
    {
        clr_TR3;
        clr_TI;
        clr_ES;
        return;
    }
#endif

#if SPL_UART1_EN > 0
    if(port == SPL_UART_PORT_1)
    {
        return;
    }
#endif
}

extern void spl_uart_deinit( uint8_t port )
{
#if SPL_UART0_EN > 0
    if( port == SPL_UART_PORT_0 )
    {
        uart0_rx_fifo.buf = NULL;
        uart0_rx_fifo.head = 0;
        uart0_rx_fifo.tail = 0;
        uart0_rx_fifo.size = 0;
        //uart0_tx_fifo.buf = NULL;
        //uart0_tx_fifo.head = 0;
        //uart0_tx_fifo.tail = 0;
        //uart0_tx_fifo.size = 0;
        return;
    }
#endif

#if SPL_UART1_EN > 0
    if( port == SPL_UART_PORT_1 )
    {
        uart1_rx_fifo.buf = NULL;
        uart1_rx_fifo.head = 0;
        uart1_rx_fifo.tail = 0;
        uart1_rx_fifo.size = 0;
        //uart1_tx_fifo.buf = NULL;
        //uart1_tx_fifo.head = 0;
        //uart1_tx_fifo.tail = 0;
        //uart1_tx_fifo.size = 0;
        return;
    }
#endif
}

#if SPL_UART0_EN > 0
extern void spl_uart0_isr( void )
{
	uint8_t u8tmp;
    
    if( RI )
    {
        clr_RI;
        /* Get the character from UART Buffer */
        u8tmp = SBUF;
        if( !fifo_buf_full(&uart0_rx_fifo) )
        {
            fifo_buf_put( &uart0_rx_fifo, u8tmp );
            SPL_UART0_CALLBACK( SPL_UART_ISR_EVT_RXD );
        }
        else
        {
            fifo_buf_flush(&uart0_rx_fifo);
            SPL_UART0_CALLBACK( SPL_UART_ISR_EVT_RXD_FULL );
        }   
    }
    
    
    if( TI )
    {
        clr_ES;
    }
}
#endif

#if SPL_UART1_EN > 0
extern void spl_uart1_isr( void )
{
	uint8_t u8tmp;
    
    if( RI )
    {
        clr_RI;
        /* Get the character from UART Buffer */
        u8tmp = SBUF;
        if( !fifo_buf_full(&uart0_rx_fifo) )
        {
            fifo_buf_put( &uart0_rx_fifo, u8tmp );
            SPL_UART0_CALLBACK( SPL_UART_ISR_EVT_RXD );
        }
        else
        {
            fifo_buf_flush(&uart0_rx_fifo);
            SPL_UART0_CALLBACK( SPL_UART_ISR_EVT_RXD_FULL );
        }   
    }
    
    
    if( TI )
    {
        clr_ES;
    }
}
#endif

