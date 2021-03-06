import os
import platform

# toolchains options
ARCH='arm'
CPU='cortex-m3'
CROSS_TOOL='gcc'
LDSTR = ' '

def list_file_dir(level, rootpath):

    global LDSTR
    for path in os.listdir(rootpath):
        absolutely_path = os.path.join(rootpath,path)
        if os.path.isdir(absolutely_path):
            list_file_dir(level+1, absolutely_path)
        else:
            LDSTR +=  ' ' + absolutely_path

list_file_dir(2,'../EASY_IO_SDK/build')


if os.getenv('RTT_CC'):
	CROSS_TOOL = os.getenv('RTT_CC')

#device options
# STM32_TYPE = 
# 'STM32F10X_LD','STM32F10X_LD_VL',
# 'STM32F10X_MD','STM32F10X_MD_VL',
# 'STM32F10X_HD','STM32F10X_HD_VL',
# 'STM32F10X_XL','STM32F10X_CL'
STM32_TYPE = 'STM32F10X_HD'

# lcd panel options
# 'FMT0371','ILI932X', 'SSD1289'
RT_USING_LCD_TYPE = 'SSD1289'

# cross_tool provides the cross compiler
# EXEC_PATH is the compiler execute path, for example, CodeSourcery, Keil MDK, IAR



#list_file_dir(2,'./build')
#print list_file_dir(2,'build')



if  CROSS_TOOL == 'gcc':
	PLATFORM 	= 'gcc'
	EXEC_PATH 	= '/opt/arm-2010.09/bin'
elif CROSS_TOOL == 'keil':
	PLATFORM 	= 'armcc'
	EXEC_PATH 	= 'C:/Keil'
elif CROSS_TOOL == 'iar':
	PLATFORM 	= 'iar'
	IAR_PATH 	= 'C:/Program Files/IAR Systems/Embedded Workbench 6.0 Evaluation'

if  platform.system() == 'Windows':
	EXEC_PATH	= 'C:/Program Files/CodeSourcery/Sourcery G++ Lite/bin'


if os.getenv('RTT_EXEC_PATH'):
	EXEC_PATH = os.getenv('RTT_EXEC_PATH')
BUILD = 'xdebug'

if PLATFORM == 'gcc':
    # toolchains
    PREFIX = 'arm-none-eabi-'
    CC = PREFIX + 'gcc'
    AS = PREFIX + 'gcc'
    AR = PREFIX + 'ar'
    LINK = PREFIX + 'gcc'
    TARGET_EXT = 'axf'
    SIZE = PREFIX + 'size'
    OBJDUMP = PREFIX + 'objdump'
    OBJCPY = PREFIX + 'objcopy'

    DEVICE = ' -mcpu=cortex-m3 -mthumb -ffunction-sections -fdata-sections'
    CFLAGS = DEVICE
    CFLAGS += ' -I../EASY_IO_SDK/ -I../../EASY_IO_SDK/STM32F10x_StdPeriph_Driver/inc/'
    AFLAGS = ' -c' + DEVICE + ' -x assembler-with-cpp'
    LFLAGS = DEVICE + ' -Wl,--gc-sections,-Map=easyio-stm32.map,-cref,-u,Reset_Handler -T ../EASY_IO_SDK/stm32_rom.ld'
    LFLAGS += LDSTR
    #print LFLAGS

    CPATH = ''
    LPATH = ''

    if BUILD == 'debug':
        AFLAGS += ' -gdwarf-2'
    else:
        CFLAGS += ' -O2'

    POST_ACTION = OBJCPY + ' -O binary $TARGET  easyio.bin\n' + SIZE + ' $TARGET \n'

elif PLATFORM == 'armcc':
    # toolchains
    CC = 'armcc'
    AS = 'armasm'
    AR = 'armar'
    LINK = 'armlink'
    TARGET_EXT = 'axf'

    DEVICE = ' --device DARMSTM'
    CFLAGS = DEVICE + ' --apcs=interwork'
    AFLAGS = DEVICE
    LFLAGS = DEVICE + ' --info sizes --info totals --info unused --info veneers --list rtthread-stm32.map --scatter stm32_rom.sct'

    CFLAGS += ' -I' + EXEC_PATH + '/ARM/RV31/INC'
    LFLAGS += ' --libpath ' + EXEC_PATH + '/ARM/RV31/LIB'

    EXEC_PATH += '/arm/bin40/'

    if BUILD == 'debug':
        CFLAGS += ' -g -O0'
        AFLAGS += ' -g'
    else:
        CFLAGS += ' -O2'
	#print 'NO 02 !!!\n'

    POST_ACTION = 'fromelf --bin $TARGET --output rtthread.bin \nfromelf -z $TARGET'

elif PLATFORM == 'iar':
    # toolchains
    CC = 'iccarm'
    AS = 'iasmarm'
    AR = 'iarchive'
    LINK = 'ilinkarm'
    TARGET_EXT = 'out'

    DEVICE = ' -D USE_STDPERIPH_DRIVER' + ' -D STM32F10X_HD'

    CFLAGS = DEVICE
    CFLAGS += ' --diag_suppress Pa050'
    CFLAGS += ' --no_cse' 
    CFLAGS += ' --no_unroll' 
    CFLAGS += ' --no_inline' 
    CFLAGS += ' --no_code_motion' 
    CFLAGS += ' --no_tbaa' 
    CFLAGS += ' --no_clustering' 
    CFLAGS += ' --no_scheduling' 
    CFLAGS += ' --debug' 
    CFLAGS += ' --endian=little' 
    CFLAGS += ' --cpu=Cortex-M3' 
    CFLAGS += ' -e' 
    CFLAGS += ' --fpu=None'
    CFLAGS += ' --dlib_config "' + IAR_PATH + '/arm/INC/c/DLib_Config_Normal.h"'    
    CFLAGS += ' -Ol'    
    CFLAGS += ' --use_c++_inline'
        
    AFLAGS = ''
    AFLAGS += ' -s+' 
    AFLAGS += ' -w+' 
    AFLAGS += ' -r' 
    AFLAGS += ' --cpu Cortex-M3' 
    AFLAGS += ' --fpu None' 

    LFLAGS = ' --config stm32f10x_flash.icf'
    LFLAGS += ' --redirect _Printf=_PrintfTiny' 
    LFLAGS += ' --redirect _Scanf=_ScanfSmall' 
    LFLAGS += ' --entry __iar_program_start'    

    EXEC_PATH = IAR_PATH + '/arm/bin/'
    POST_ACTION = ''
