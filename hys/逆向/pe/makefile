
cc = cl
args = /nologo /Fe
# 预定义宏
macro = # /D "_UNICODE" /D "UNICODE" /D "_AMD64_" /D "RC_INVOKED" /D "_CONSOLE" 

hello: helloworld.c
	$(cc) $(args)helloworld1.exe helloworld.c

pe: is_pe.c
	$(cc) $(macro) $(args)is_pe.exe is_pe.c
	is_pe.exe

clean:
	del *.obj
	del *.pdb
	del *.ilk
	del *.exp
	del *.map
	del *.asm