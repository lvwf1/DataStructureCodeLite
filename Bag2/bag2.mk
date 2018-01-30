##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=bag2
ConfigurationName      :=Debug
WorkspacePath          := "C:\Users\Weifeng\Desktop\Everything\Data Structure\CodeLite"
ProjectPath            := "C:\Users\Weifeng\Desktop\Everything\Data Structure\CodeLite\Bag2"
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Weifeng
Date                   :=04/02/2016
CodeLitePath           :="C:\Program Files\CodeLite"
LinkerName             :=C:/TDM-GCC-64/bin/g++.exe
SharedObjectLinkerName :=C:/TDM-GCC-64/bin/g++.exe -shared -fPIC
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
ObjectsFileList        :="bag2.txt"
PCHCompileFlags        :=
MakeDirCommand         :=makedir
RcCmpOptions           := 
RcCompilerName         :=C:/TDM-GCC-64/bin/windres.exe
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := C:/TDM-GCC-64/bin/ar.exe rcu
CXX      := C:/TDM-GCC-64/bin/g++.exe
CC       := C:/TDM-GCC-64/bin/gcc.exe
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := C:/TDM-GCC-64/bin/as.exe


##
## User defined environment variables
##
CodeLiteDir:=C:\Program Files\CodeLite
Objects0=$(IntermediateDirectory)/bag2.cpp$(ObjectSuffix) $(IntermediateDirectory)/bag2demo.cpp$(ObjectSuffix) 



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
$(IntermediateDirectory)/bag2.cpp$(ObjectSuffix): bag2.cpp $(IntermediateDirectory)/bag2.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/Weifeng/Desktop/Everything/Data Structure/CodeLite/Bag2/bag2.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/bag2.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/bag2.cpp$(DependSuffix): bag2.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/bag2.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/bag2.cpp$(DependSuffix) -MM "bag2.cpp"

$(IntermediateDirectory)/bag2.cpp$(PreprocessSuffix): bag2.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/bag2.cpp$(PreprocessSuffix) "bag2.cpp"

$(IntermediateDirectory)/bag2demo.cpp$(ObjectSuffix): bag2demo.cpp $(IntermediateDirectory)/bag2demo.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/Weifeng/Desktop/Everything/Data Structure/CodeLite/Bag2/bag2demo.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/bag2demo.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/bag2demo.cpp$(DependSuffix): bag2demo.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/bag2demo.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/bag2demo.cpp$(DependSuffix) -MM "bag2demo.cpp"

$(IntermediateDirectory)/bag2demo.cpp$(PreprocessSuffix): bag2demo.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/bag2demo.cpp$(PreprocessSuffix) "bag2demo.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


