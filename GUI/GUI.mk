##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=GUI
ConfigurationName      :=Debug
WorkspacePath          :=C:/Users/mohammad/Documents/Codelite/tbstudio
ProjectPath            :=C:/Users/mohammad/Documents/Codelite/tbstudio/GUI
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=mohammad
Date                   :=14/05/2023
CodeLitePath           :="C:/Program Files/CodeLite"
LinkerName             :=C:/TDM-GCC-64/bin/g++.exe
SharedObjectLinkerName :=C:/TDM-GCC-64/g++.exe -shared -fPIC
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
ObjectsFileList        :="GUI.txt"
PCHCompileFlags        :=
MakeDirCommand         :=makedir
RcCmpOptions           := $(shell wx-config --rcflags)
RcCompilerName         :=C:/TDM-GCC-64/bin/windres.exe
LinkOptions            :=  -mwindows $(shell wx-config --libs std,gl,ribbon) -mwindows -std=gnu++11 -pthread -liphlpapi -IC:\Users\mohammad\Documents\Codelite\pecsjunc\LAPACKE-X64 -llapacke
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). $(IncludeSwitch)$(MathGL_DIR)/include $(IncludeSwitch)$(Glut_DIR)/include $(IncludeSwitch)$(LAPACKE_DIR) $(IncludeSwitch)$(Gemmi_DIR)/include $(IncludeSwitch)$(RapidXML_DIR) $(IncludeSwitch)$(SimpleJSON_DIR) $(IncludeSwitch)$(RapidJSON_DIR) 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)mgl-glut $(LibrarySwitch)mgl $(LibrarySwitch)freeglut 
ArLibs                 :=  "libmgl-glut.a" "libmgl.a" "libfreeglut.a" 
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch)$(Opengl_DIR) $(LibraryPathSwitch)$(MathGL_DIR)\lib $(LibraryPathSwitch)C:\TDM-GCC-64\x86_64-w64-mingw32\lib $(LibraryPathSwitch)$(Glut_DIR)\lib $(LibraryPathSwitch)$(LAPACKE_DIR) $(LibraryPathSwitch)C:\TDM-GCC-64\gcc-10.3.0-tdm64-1-fortran\bin 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := C:/TDM-GCC-64/bin/ar.exe rcu
CXX      := C:/TDM-GCC-64/bin/g++.exe
CC       := C:/TDM-GCC-64/bin/gcc.exe
CXXFLAGS :=  -g -O0 -Wall $(shell wx-config --cxxflags --gl-libs) $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := C:/TDM-GCC-64/bin/as.exe


##
## User defined environment variables
##
CodeLiteDir:=C:\Program Files\CodeLite
WXWIN:=C:\wxWidgets-3.2.0
GCC_DIR:=C:\TDM-GCC-64
GFORTRAN_DIR:=C:\gcc-10.3.0-tdm64-1-fortran
WXCFG:=gcc_dll\mswu
Opengl_DIR:=$(GCC_DIR)\x86_64-w64-mingw32\lib
MathGL_DIR:=C:\Users\mohammad\Documents\Codelite\pecsjunc\MathGL64LGPL
LAPACKE_DIR:=C:\Users\mohammad\Documents\Codelite\pecsjunc\LAPACKE-X64
Glut_DIR:=C:\Users\mohammad\Documents\Codelite\pecsjunc\freeglut64
Gemmi_DIR:=C:\Users\mohammad\Documents\Codelite\pecsjunc\gemmi-master
RapidXML_DIR:=C:\Users\mohammad\Documents\Codelite\tbstudio\rapidxml-1.13
RapidJSON_DIR:=C:\Users\mohammad\Documents\Codelite\tbstudio\rapidjson-1.1.0
SimpleJSON_DIR:=C:\Users\mohammad\Documents\Codelite\tbstudio\simpleJSON
PATH:=$(WXWIN)\lib\gcc_dll;$(GCC_DIR)\bin;$(PATH)
PATH:=C:\Users\mohammad\Documents\Codelite\pecsjunc\MathGL64LGPL\bin;$(PATH)
PATH:=$(Glut_DIR)\bin;$(PATH)
PATH:=$(LAPACKE_DIR);$(PATH)
PATH:=$(GFORTRAN_DIR)\bin;$(PATH)
Objects0=$(IntermediateDirectory)/win_resources.rc$(ObjectSuffix) $(IntermediateDirectory)/Sec30.cpp$(ObjectSuffix) $(IntermediateDirectory)/StructureClass.cpp$(ObjectSuffix) $(IntermediateDirectory)/checktree.cpp$(ObjectSuffix) $(IntermediateDirectory)/Regression.cpp$(ObjectSuffix) $(IntermediateDirectory)/UnitcellClass.cpp$(ObjectSuffix) $(IntermediateDirectory)/SKClass.cpp$(ObjectSuffix) $(IntermediateDirectory)/SetupClass.cpp$(ObjectSuffix) $(IntermediateDirectory)/wxcrafter.cpp$(ObjectSuffix) $(IntermediateDirectory)/WelcomeClass.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/BondsClass.cpp$(ObjectSuffix) $(IntermediateDirectory)/OrbitalsClass.cpp$(ObjectSuffix) $(IntermediateDirectory)/NomadGUI.cpp$(ObjectSuffix) $(IntermediateDirectory)/Nomad.cpp$(ObjectSuffix) $(IntermediateDirectory)/MyFigureClass.cpp$(ObjectSuffix) $(IntermediateDirectory)/UpdateClass.cpp$(ObjectSuffix) $(IntermediateDirectory)/MyMatrix.cpp$(ObjectSuffix) $(IntermediateDirectory)/sec30TextCtrl.cpp$(ObjectSuffix) $(IntermediateDirectory)/mygrid.cpp$(ObjectSuffix) $(IntermediateDirectory)/GridClass.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/GraphClass.cpp$(ObjectSuffix) $(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IntermediateDirectory)/MainFrame.cpp$(ObjectSuffix) $(IntermediateDirectory)/wxcrafter_bitmaps.cpp$(ObjectSuffix) $(IntermediateDirectory)/MyOpenGL.cpp$(ObjectSuffix) $(IntermediateDirectory)/ColorsClass.cpp$(ObjectSuffix) $(IntermediateDirectory)/LoginClass.cpp$(ObjectSuffix) 



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

PostBuild:
	@echo Executing Post Build commands ...
	
	@echo Done

MakeIntermediateDirs:
	@$(MakeDirCommand) "./Debug"


$(IntermediateDirectory)/.d:
	@$(MakeDirCommand) "./Debug"

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/win_resources.rc$(ObjectSuffix): win_resources.rc
	$(RcCompilerName) -i "C:/Users/mohammad/Documents/Codelite/tbstudio/GUI/win_resources.rc" $(RcCmpOptions)   $(ObjectSwitch)$(IntermediateDirectory)/win_resources.rc$(ObjectSuffix) $(RcIncludePath)
$(IntermediateDirectory)/Sec30.cpp$(ObjectSuffix): Sec30.cpp $(IntermediateDirectory)/Sec30.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/mohammad/Documents/Codelite/tbstudio/GUI/Sec30.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Sec30.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Sec30.cpp$(DependSuffix): Sec30.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Sec30.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Sec30.cpp$(DependSuffix) -MM Sec30.cpp

$(IntermediateDirectory)/Sec30.cpp$(PreprocessSuffix): Sec30.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Sec30.cpp$(PreprocessSuffix) Sec30.cpp

$(IntermediateDirectory)/StructureClass.cpp$(ObjectSuffix): StructureClass.cpp $(IntermediateDirectory)/StructureClass.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/mohammad/Documents/Codelite/tbstudio/GUI/StructureClass.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/StructureClass.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/StructureClass.cpp$(DependSuffix): StructureClass.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/StructureClass.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/StructureClass.cpp$(DependSuffix) -MM StructureClass.cpp

$(IntermediateDirectory)/StructureClass.cpp$(PreprocessSuffix): StructureClass.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/StructureClass.cpp$(PreprocessSuffix) StructureClass.cpp

$(IntermediateDirectory)/checktree.cpp$(ObjectSuffix): checktree.cpp $(IntermediateDirectory)/checktree.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/mohammad/Documents/Codelite/tbstudio/GUI/checktree.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/checktree.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/checktree.cpp$(DependSuffix): checktree.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/checktree.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/checktree.cpp$(DependSuffix) -MM checktree.cpp

$(IntermediateDirectory)/checktree.cpp$(PreprocessSuffix): checktree.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/checktree.cpp$(PreprocessSuffix) checktree.cpp

$(IntermediateDirectory)/Regression.cpp$(ObjectSuffix): Regression.cpp $(IntermediateDirectory)/Regression.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/mohammad/Documents/Codelite/tbstudio/GUI/Regression.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Regression.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Regression.cpp$(DependSuffix): Regression.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Regression.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Regression.cpp$(DependSuffix) -MM Regression.cpp

$(IntermediateDirectory)/Regression.cpp$(PreprocessSuffix): Regression.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Regression.cpp$(PreprocessSuffix) Regression.cpp

$(IntermediateDirectory)/UnitcellClass.cpp$(ObjectSuffix): UnitcellClass.cpp $(IntermediateDirectory)/UnitcellClass.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/mohammad/Documents/Codelite/tbstudio/GUI/UnitcellClass.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/UnitcellClass.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/UnitcellClass.cpp$(DependSuffix): UnitcellClass.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/UnitcellClass.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/UnitcellClass.cpp$(DependSuffix) -MM UnitcellClass.cpp

$(IntermediateDirectory)/UnitcellClass.cpp$(PreprocessSuffix): UnitcellClass.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/UnitcellClass.cpp$(PreprocessSuffix) UnitcellClass.cpp

$(IntermediateDirectory)/SKClass.cpp$(ObjectSuffix): SKClass.cpp $(IntermediateDirectory)/SKClass.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/mohammad/Documents/Codelite/tbstudio/GUI/SKClass.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/SKClass.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/SKClass.cpp$(DependSuffix): SKClass.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/SKClass.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/SKClass.cpp$(DependSuffix) -MM SKClass.cpp

$(IntermediateDirectory)/SKClass.cpp$(PreprocessSuffix): SKClass.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/SKClass.cpp$(PreprocessSuffix) SKClass.cpp

$(IntermediateDirectory)/SetupClass.cpp$(ObjectSuffix): SetupClass.cpp $(IntermediateDirectory)/SetupClass.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/mohammad/Documents/Codelite/tbstudio/GUI/SetupClass.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/SetupClass.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/SetupClass.cpp$(DependSuffix): SetupClass.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/SetupClass.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/SetupClass.cpp$(DependSuffix) -MM SetupClass.cpp

$(IntermediateDirectory)/SetupClass.cpp$(PreprocessSuffix): SetupClass.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/SetupClass.cpp$(PreprocessSuffix) SetupClass.cpp

$(IntermediateDirectory)/wxcrafter.cpp$(ObjectSuffix): wxcrafter.cpp $(IntermediateDirectory)/wxcrafter.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/mohammad/Documents/Codelite/tbstudio/GUI/wxcrafter.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/wxcrafter.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/wxcrafter.cpp$(DependSuffix): wxcrafter.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/wxcrafter.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/wxcrafter.cpp$(DependSuffix) -MM wxcrafter.cpp

$(IntermediateDirectory)/wxcrafter.cpp$(PreprocessSuffix): wxcrafter.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/wxcrafter.cpp$(PreprocessSuffix) wxcrafter.cpp

$(IntermediateDirectory)/WelcomeClass.cpp$(ObjectSuffix): WelcomeClass.cpp $(IntermediateDirectory)/WelcomeClass.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/mohammad/Documents/Codelite/tbstudio/GUI/WelcomeClass.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/WelcomeClass.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/WelcomeClass.cpp$(DependSuffix): WelcomeClass.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/WelcomeClass.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/WelcomeClass.cpp$(DependSuffix) -MM WelcomeClass.cpp

$(IntermediateDirectory)/WelcomeClass.cpp$(PreprocessSuffix): WelcomeClass.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/WelcomeClass.cpp$(PreprocessSuffix) WelcomeClass.cpp

$(IntermediateDirectory)/BondsClass.cpp$(ObjectSuffix): BondsClass.cpp $(IntermediateDirectory)/BondsClass.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/mohammad/Documents/Codelite/tbstudio/GUI/BondsClass.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/BondsClass.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/BondsClass.cpp$(DependSuffix): BondsClass.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/BondsClass.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/BondsClass.cpp$(DependSuffix) -MM BondsClass.cpp

$(IntermediateDirectory)/BondsClass.cpp$(PreprocessSuffix): BondsClass.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/BondsClass.cpp$(PreprocessSuffix) BondsClass.cpp

$(IntermediateDirectory)/OrbitalsClass.cpp$(ObjectSuffix): OrbitalsClass.cpp $(IntermediateDirectory)/OrbitalsClass.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/mohammad/Documents/Codelite/tbstudio/GUI/OrbitalsClass.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/OrbitalsClass.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/OrbitalsClass.cpp$(DependSuffix): OrbitalsClass.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/OrbitalsClass.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/OrbitalsClass.cpp$(DependSuffix) -MM OrbitalsClass.cpp

$(IntermediateDirectory)/OrbitalsClass.cpp$(PreprocessSuffix): OrbitalsClass.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/OrbitalsClass.cpp$(PreprocessSuffix) OrbitalsClass.cpp

$(IntermediateDirectory)/NomadGUI.cpp$(ObjectSuffix): NomadGUI.cpp $(IntermediateDirectory)/NomadGUI.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/mohammad/Documents/Codelite/tbstudio/GUI/NomadGUI.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/NomadGUI.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/NomadGUI.cpp$(DependSuffix): NomadGUI.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/NomadGUI.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/NomadGUI.cpp$(DependSuffix) -MM NomadGUI.cpp

$(IntermediateDirectory)/NomadGUI.cpp$(PreprocessSuffix): NomadGUI.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/NomadGUI.cpp$(PreprocessSuffix) NomadGUI.cpp

$(IntermediateDirectory)/Nomad.cpp$(ObjectSuffix): Nomad.cpp $(IntermediateDirectory)/Nomad.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/mohammad/Documents/Codelite/tbstudio/GUI/Nomad.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Nomad.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Nomad.cpp$(DependSuffix): Nomad.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Nomad.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Nomad.cpp$(DependSuffix) -MM Nomad.cpp

$(IntermediateDirectory)/Nomad.cpp$(PreprocessSuffix): Nomad.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Nomad.cpp$(PreprocessSuffix) Nomad.cpp

$(IntermediateDirectory)/MyFigureClass.cpp$(ObjectSuffix): MyFigureClass.cpp $(IntermediateDirectory)/MyFigureClass.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/mohammad/Documents/Codelite/tbstudio/GUI/MyFigureClass.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/MyFigureClass.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/MyFigureClass.cpp$(DependSuffix): MyFigureClass.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/MyFigureClass.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/MyFigureClass.cpp$(DependSuffix) -MM MyFigureClass.cpp

$(IntermediateDirectory)/MyFigureClass.cpp$(PreprocessSuffix): MyFigureClass.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/MyFigureClass.cpp$(PreprocessSuffix) MyFigureClass.cpp

$(IntermediateDirectory)/UpdateClass.cpp$(ObjectSuffix): UpdateClass.cpp $(IntermediateDirectory)/UpdateClass.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/mohammad/Documents/Codelite/tbstudio/GUI/UpdateClass.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/UpdateClass.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/UpdateClass.cpp$(DependSuffix): UpdateClass.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/UpdateClass.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/UpdateClass.cpp$(DependSuffix) -MM UpdateClass.cpp

$(IntermediateDirectory)/UpdateClass.cpp$(PreprocessSuffix): UpdateClass.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/UpdateClass.cpp$(PreprocessSuffix) UpdateClass.cpp

$(IntermediateDirectory)/MyMatrix.cpp$(ObjectSuffix): MyMatrix.cpp $(IntermediateDirectory)/MyMatrix.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/mohammad/Documents/Codelite/tbstudio/GUI/MyMatrix.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/MyMatrix.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/MyMatrix.cpp$(DependSuffix): MyMatrix.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/MyMatrix.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/MyMatrix.cpp$(DependSuffix) -MM MyMatrix.cpp

$(IntermediateDirectory)/MyMatrix.cpp$(PreprocessSuffix): MyMatrix.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/MyMatrix.cpp$(PreprocessSuffix) MyMatrix.cpp

$(IntermediateDirectory)/sec30TextCtrl.cpp$(ObjectSuffix): sec30TextCtrl.cpp $(IntermediateDirectory)/sec30TextCtrl.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/mohammad/Documents/Codelite/tbstudio/GUI/sec30TextCtrl.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/sec30TextCtrl.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/sec30TextCtrl.cpp$(DependSuffix): sec30TextCtrl.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/sec30TextCtrl.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/sec30TextCtrl.cpp$(DependSuffix) -MM sec30TextCtrl.cpp

$(IntermediateDirectory)/sec30TextCtrl.cpp$(PreprocessSuffix): sec30TextCtrl.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/sec30TextCtrl.cpp$(PreprocessSuffix) sec30TextCtrl.cpp

$(IntermediateDirectory)/mygrid.cpp$(ObjectSuffix): mygrid.cpp $(IntermediateDirectory)/mygrid.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/mohammad/Documents/Codelite/tbstudio/GUI/mygrid.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/mygrid.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/mygrid.cpp$(DependSuffix): mygrid.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/mygrid.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/mygrid.cpp$(DependSuffix) -MM mygrid.cpp

$(IntermediateDirectory)/mygrid.cpp$(PreprocessSuffix): mygrid.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/mygrid.cpp$(PreprocessSuffix) mygrid.cpp

$(IntermediateDirectory)/GridClass.cpp$(ObjectSuffix): GridClass.cpp $(IntermediateDirectory)/GridClass.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/mohammad/Documents/Codelite/tbstudio/GUI/GridClass.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/GridClass.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/GridClass.cpp$(DependSuffix): GridClass.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/GridClass.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/GridClass.cpp$(DependSuffix) -MM GridClass.cpp

$(IntermediateDirectory)/GridClass.cpp$(PreprocessSuffix): GridClass.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/GridClass.cpp$(PreprocessSuffix) GridClass.cpp

$(IntermediateDirectory)/GraphClass.cpp$(ObjectSuffix): GraphClass.cpp $(IntermediateDirectory)/GraphClass.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/mohammad/Documents/Codelite/tbstudio/GUI/GraphClass.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/GraphClass.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/GraphClass.cpp$(DependSuffix): GraphClass.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/GraphClass.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/GraphClass.cpp$(DependSuffix) -MM GraphClass.cpp

$(IntermediateDirectory)/GraphClass.cpp$(PreprocessSuffix): GraphClass.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/GraphClass.cpp$(PreprocessSuffix) GraphClass.cpp

$(IntermediateDirectory)/main.cpp$(ObjectSuffix): main.cpp $(IntermediateDirectory)/main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/mohammad/Documents/Codelite/tbstudio/GUI/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.cpp$(DependSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/main.cpp$(DependSuffix) -MM main.cpp

$(IntermediateDirectory)/main.cpp$(PreprocessSuffix): main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.cpp$(PreprocessSuffix) main.cpp

$(IntermediateDirectory)/MainFrame.cpp$(ObjectSuffix): MainFrame.cpp $(IntermediateDirectory)/MainFrame.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/mohammad/Documents/Codelite/tbstudio/GUI/MainFrame.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/MainFrame.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/MainFrame.cpp$(DependSuffix): MainFrame.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/MainFrame.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/MainFrame.cpp$(DependSuffix) -MM MainFrame.cpp

$(IntermediateDirectory)/MainFrame.cpp$(PreprocessSuffix): MainFrame.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/MainFrame.cpp$(PreprocessSuffix) MainFrame.cpp

$(IntermediateDirectory)/wxcrafter_bitmaps.cpp$(ObjectSuffix): wxcrafter_bitmaps.cpp $(IntermediateDirectory)/wxcrafter_bitmaps.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/mohammad/Documents/Codelite/tbstudio/GUI/wxcrafter_bitmaps.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/wxcrafter_bitmaps.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/wxcrafter_bitmaps.cpp$(DependSuffix): wxcrafter_bitmaps.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/wxcrafter_bitmaps.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/wxcrafter_bitmaps.cpp$(DependSuffix) -MM wxcrafter_bitmaps.cpp

$(IntermediateDirectory)/wxcrafter_bitmaps.cpp$(PreprocessSuffix): wxcrafter_bitmaps.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/wxcrafter_bitmaps.cpp$(PreprocessSuffix) wxcrafter_bitmaps.cpp

$(IntermediateDirectory)/MyOpenGL.cpp$(ObjectSuffix): MyOpenGL.cpp $(IntermediateDirectory)/MyOpenGL.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/mohammad/Documents/Codelite/tbstudio/GUI/MyOpenGL.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/MyOpenGL.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/MyOpenGL.cpp$(DependSuffix): MyOpenGL.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/MyOpenGL.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/MyOpenGL.cpp$(DependSuffix) -MM MyOpenGL.cpp

$(IntermediateDirectory)/MyOpenGL.cpp$(PreprocessSuffix): MyOpenGL.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/MyOpenGL.cpp$(PreprocessSuffix) MyOpenGL.cpp

$(IntermediateDirectory)/ColorsClass.cpp$(ObjectSuffix): ColorsClass.cpp $(IntermediateDirectory)/ColorsClass.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/mohammad/Documents/Codelite/tbstudio/GUI/ColorsClass.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ColorsClass.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ColorsClass.cpp$(DependSuffix): ColorsClass.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/ColorsClass.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/ColorsClass.cpp$(DependSuffix) -MM ColorsClass.cpp

$(IntermediateDirectory)/ColorsClass.cpp$(PreprocessSuffix): ColorsClass.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ColorsClass.cpp$(PreprocessSuffix) ColorsClass.cpp

$(IntermediateDirectory)/LoginClass.cpp$(ObjectSuffix): LoginClass.cpp $(IntermediateDirectory)/LoginClass.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/mohammad/Documents/Codelite/tbstudio/GUI/LoginClass.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/LoginClass.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/LoginClass.cpp$(DependSuffix): LoginClass.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/LoginClass.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/LoginClass.cpp$(DependSuffix) -MM LoginClass.cpp

$(IntermediateDirectory)/LoginClass.cpp$(PreprocessSuffix): LoginClass.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/LoginClass.cpp$(PreprocessSuffix) LoginClass.cpp


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


