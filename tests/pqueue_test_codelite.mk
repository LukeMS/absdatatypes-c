##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=pqueue_test_codelite
ConfigurationName      :=Debug
WorkspacePath          :=C:/Users/Lucas/Documents/cc/absdatatypes
ProjectPath            :=C:/Users/Lucas/Documents/cc/absdatatypes/tests
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Lucas
Date                   :=13/07/2017
CodeLitePath           :="C:/Program Files (x86)/CodeLite"
LinkerName             :=C:/msys32/mingw32/bin/i686-w64-mingw32-g++.exe
SharedObjectLinkerName :=C:/msys32/mingw32/bin/i686-w64-mingw32-g++.exe -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="pqueue_test_codelite.txt"
PCHCompileFlags        :=
MakeDirCommand         :=makedir
RcCmpOptions           := 
RcCompilerName         :=windres
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). $(IncludeSwitch)../inc 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)absdatatypes 
ArLibs                 :=  "absdatatypes" 
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch)../ 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := C:/msys32/mingw32/bin/i686-w64-mingw32-ar.exe rcu
CXX      := C:/msys32/mingw32/bin/i686-w64-mingw32-g++.exe
CC       := C:/msys32/mingw32/bin/i686-w64-mingw32-gcc.exe
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := C:/msys32/mingw32/bin/i686-w64-mingw32-as.exe


##
## User defined environment variables
##
CodeLiteDir:=C:\Program Files (x86)\CodeLite
Objects0=$(IntermediateDirectory)/pqueue_test.c$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@$(MakeDirCommand) "./Debug"


$(IntermediateDirectory)/.d:
	@$(MakeDirCommand) "./Debug"

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/pqueue_test.c$(ObjectSuffix): pqueue_test.c $(IntermediateDirectory)/pqueue_test.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Users/Lucas/Documents/cc/absdatatypes/tests/pqueue_test.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/pqueue_test.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/pqueue_test.c$(DependSuffix): pqueue_test.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/pqueue_test.c$(ObjectSuffix) -MF$(IntermediateDirectory)/pqueue_test.c$(DependSuffix) -MM pqueue_test.c

$(IntermediateDirectory)/pqueue_test.c$(PreprocessSuffix): pqueue_test.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/pqueue_test.c$(PreprocessSuffix)pqueue_test.c


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


