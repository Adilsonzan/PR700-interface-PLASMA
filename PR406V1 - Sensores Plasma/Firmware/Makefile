#diretorio bin do compilador
#GCCPTH=C:\Program Files (x86)\HI-TECH Software\PICC-18\PRO\9.80\bin
GCCPTH=C:\Program Files (x86)\HI-TECH Software\PICC-18\9.80\bin
#compiladores
CC="$(GCCPTH)\picc18.exe"
LD="$(GCCPTH)\picc18.exe"
RM=del
FS="D:\Programas\eclipse_pic\filesig\filesig.exe"

#parametros passados ambos para o compilador e linker
FCHIP=--chip=18F45K22
FFORMAT="--errformat=%%f:%%l: Error: %%s (%%n)" "--msgformat=%%f:%%l: Advisory: %%s (%%n)" "--warnformat=%%f:%%l: warning: %%s (%%n)"
FRUNTIME=--runtime=default,+clear,+init,-keep,-download,+stackwarn,-config,+clib,-plib
FOPTION=--opt=default,+asm,-debug,+speed,-space,9
FMEMORY=--rom=default --ram=default -Blarge
FCONFIG=--warn=0 --double=24 --float=24 --cp=24 --addrqual=ignore -g

#compilador
CCFLAGS=$(FCHIP) $(INC) -P $(FRUNTIME) $(FOPTION) $(FMEMORY) $(FCONFIG) $(FFORMAT) --OBJDIR="$(OBJPTH)" --OUTDIR="$(OBJPTH)" 

#linker
FSUMMARY=--summary=default,-psect,-class,+mem,-hex
FOUTPUT=--output=default,-inhx032
LDFLAGS=$(SUMMARY) $(FOUTPUT) $(CCFLAGS)

#caminhos
PRJPTH=$(PWD)
HEXPTH=$(PRJPTH)\hex
OBJPTH=$(PRJPTH)\obj
#LIBPTH=D:\prog\lib_mcu_pic
PRJSRC=$(PRJPTH)\src
LIBSRC=$(LIBPTH)\src

#arquivos
SRC=
SRC+="$(PRJSRC)\main.c"
#SRC+="$(PRJSRC)\xsystem.c"

#todos os includes necesários
INC=
INC+="-I$(PRJPTH)\src"
#INC+="-I$(LIBPTH)\inc"

main=pr406v1-sens_plasma
HEX=$(main).hex

#compilação
all:
	@echo Compilando...
	@$(CC) --pass1 $(SRC) -q $(CCFLAGS)
	@echo Linkando...
	@$(LD) -o$(HEX) $(SRC:.c=.p1) $(LDFLAGS)
	@copy "$(OBJPTH)\$(HEX)" "$(HEXPTH)\$(HEX)"
	@$(FS) "$(HEXPTH)\$(HEX)" pr184v3
	@del funclist 

#limpeza dos arquivos
clean : 
	$(RM) "$(OBJPTH)\*.*" /q	
	$(RM) "$(HEXPTH)\*.*" /q
