##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Release
ProjectName            :=GUI
ConfigurationName      :=Release
WorkspacePath          :=${GITHUB_WORKSPACE}
ProjectPath            :=${GITHUB_WORKSPACE}/GUI
IntermediateDirectory  :=./Release
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=MohammadNakhaee
Date                   :=18/11/2019
CodeLitePath           :="/Users/mohammadnakhaee/Library/Application Support/CodeLite"
LinkerName             :=/usr/local/opt/llvm/bin/clang++
SharedObjectLinkerName :=/usr/local/opt/llvm/bin/clang++ -dynamiclib -fPIC
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
Preprocessors          :=$(PreprocessorSwitch)NDEBUG 
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="GUI.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  $(shell wx-config --libs std,gl,ribbon,aui,richtext) -std=gnu++11 -framework OpenGL -framework GLUT -lX11 -lm
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). $(IncludeSwitch)$(RapidXML_DIR) $(IncludeSwitch)$(WXDIRInclude) $(IncludeSwitch)$(MATHGL_INCLUDE) $(IncludeSwitch)$(LAPACKE_INCLUDE) $(IncludeSwitch)/usr/local/opt/llvm/include 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)mgl $(LibrarySwitch)lapacke $(LibrarySwitch)lapack $(LibrarySwitch)blas $(LibrarySwitch)m 
ArLibs                 :=  "libmgl.a" "liblapacke" "liblapack" "libblas" "m" 
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch). $(LibraryPathSwitch)/usr/local/bin $(LibraryPathSwitch)/usr/local/opt/llvm/lib $(LibraryPathSwitch)/opt/local/lib $(LibraryPathSwitch)/usr/local/opt/lapack/lib $(LibraryPathSwitch)/System/Library/Frameworks/GLUT.framework 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/local/opt/llvm/bin/ar rcu
CXX      := /usr/local/opt/llvm/bin/clang++
CC       := /usr/local/opt/llvm/bin/clang
CXXFLAGS :=  -O2 $(shell wx-config --cxxflags --gl-libs) -Wno-write-strings -mmacosx-version-min=10.14 -Wl,-rpath=. $(Preprocessors)
CFLAGS   :=  -O2 $(shell wx-config --cflags --gl-libs) $(Preprocessors)
ASFLAGS  := 
AS       := /usr/local/opt/llvm/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/Applications/codelite.app/Contents/SharedSupport/
WXDIRInclude:=/usr/local/include/wx-3.0
MATHGL_INCLUDE:=/opt/local/include
LAPACKE_INCLUDE:=/usr/local/opt/lapack/include
RapidXML_DIR:=/Users/mohammadnakhaee/Documents/tbstudio/rapidxml-1.13
PATH:=/usr/local/bin:$PATH
PATH:="/usr/local/opt/llvm/bin:$PATH"
Objects0=$(IntermediateDirectory)/mygrid.cpp$(ObjectSuffix) $(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IntermediateDirectory)/GraphClass.cpp$(ObjectSuffix) $(IntermediateDirectory)/BondsClass.cpp$(ObjectSuffix) $(IntermediateDirectory)/MyOpenGL.cpp$(ObjectSuffix) $(IntermediateDirectory)/GridClass.cpp$(ObjectSuffix) $(IntermediateDirectory)/SetupClass.cpp$(ObjectSuffix) $(IntermediateDirectory)/WelcomeClass.cpp$(ObjectSuffix) $(IntermediateDirectory)/wxcrafter_bitmaps.cpp$(ObjectSuffix) $(IntermediateDirectory)/OrbitalsClass.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/UnitcellClass.cpp$(ObjectSuffix) $(IntermediateDirectory)/SKClass.cpp$(ObjectSuffix) $(IntermediateDirectory)/wxcrafter.cpp$(ObjectSuffix) $(IntermediateDirectory)/ColorsClass.cpp$(ObjectSuffix) $(IntermediateDirectory)/checktree.cpp$(ObjectSuffix) $(IntermediateDirectory)/MyMatrix.cpp$(ObjectSuffix) $(IntermediateDirectory)/sec30TextCtrl.cpp$(ObjectSuffix) $(IntermediateDirectory)/Sec30.cpp$(ObjectSuffix) $(IntermediateDirectory)/Regression.cpp$(ObjectSuffix) $(IntermediateDirectory)/MyFigureClass.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/StructureClass.cpp$(ObjectSuffix) $(IntermediateDirectory)/MainFrame.cpp$(ObjectSuffix) $(IntermediateDirectory)/UpdateClass.cpp$(ObjectSuffix) 



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
	@test -d ./Release || $(MakeDirCommand) ./Release


$(IntermediateDirectory)/.d:
	@test -d ./Release || $(MakeDirCommand) ./Release

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/mygrid.cpp$(ObjectSuffix): mygrid.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/mygrid.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/mygrid.cpp$(DependSuffix) -MM mygrid.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Users/mohammadnakhaee/Documents/tbstudio/GUI/mygrid.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/mygrid.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/mygrid.cpp$(PreprocessSuffix): mygrid.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/mygrid.cpp$(PreprocessSuffix) mygrid.cpp

$(IntermediateDirectory)/main.cpp$(ObjectSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/main.cpp$(DependSuffix) -MM main.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Users/mohammadnakhaee/Documents/tbstudio/GUI/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.cpp$(PreprocessSuffix): main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.cpp$(PreprocessSuffix) main.cpp

$(IntermediateDirectory)/GraphClass.cpp$(ObjectSuffix): GraphClass.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/GraphClass.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/GraphClass.cpp$(DependSuffix) -MM GraphClass.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Users/mohammadnakhaee/Documents/tbstudio/GUI/GraphClass.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/GraphClass.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/GraphClass.cpp$(PreprocessSuffix): GraphClass.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/GraphClass.cpp$(PreprocessSuffix) GraphClass.cpp

$(IntermediateDirectory)/BondsClass.cpp$(ObjectSuffix): BondsClass.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/BondsClass.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/BondsClass.cpp$(DependSuffix) -MM BondsClass.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Users/mohammadnakhaee/Documents/tbstudio/GUI/BondsClass.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/BondsClass.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/BondsClass.cpp$(PreprocessSuffix): BondsClass.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/BondsClass.cpp$(PreprocessSuffix) BondsClass.cpp

$(IntermediateDirectory)/MyOpenGL.cpp$(ObjectSuffix): MyOpenGL.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/MyOpenGL.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/MyOpenGL.cpp$(DependSuffix) -MM MyOpenGL.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Users/mohammadnakhaee/Documents/tbstudio/GUI/MyOpenGL.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/MyOpenGL.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/MyOpenGL.cpp$(PreprocessSuffix): MyOpenGL.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/MyOpenGL.cpp$(PreprocessSuffix) MyOpenGL.cpp

$(IntermediateDirectory)/GridClass.cpp$(ObjectSuffix): GridClass.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/GridClass.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/GridClass.cpp$(DependSuffix) -MM GridClass.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Users/mohammadnakhaee/Documents/tbstudio/GUI/GridClass.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/GridClass.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/GridClass.cpp$(PreprocessSuffix): GridClass.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/GridClass.cpp$(PreprocessSuffix) GridClass.cpp

$(IntermediateDirectory)/SetupClass.cpp$(ObjectSuffix): SetupClass.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/SetupClass.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/SetupClass.cpp$(DependSuffix) -MM SetupClass.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Users/mohammadnakhaee/Documents/tbstudio/GUI/SetupClass.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/SetupClass.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/SetupClass.cpp$(PreprocessSuffix): SetupClass.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/SetupClass.cpp$(PreprocessSuffix) SetupClass.cpp

$(IntermediateDirectory)/WelcomeClass.cpp$(ObjectSuffix): WelcomeClass.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/WelcomeClass.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/WelcomeClass.cpp$(DependSuffix) -MM WelcomeClass.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Users/mohammadnakhaee/Documents/tbstudio/GUI/WelcomeClass.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/WelcomeClass.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/WelcomeClass.cpp$(PreprocessSuffix): WelcomeClass.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/WelcomeClass.cpp$(PreprocessSuffix) WelcomeClass.cpp

$(IntermediateDirectory)/wxcrafter_bitmaps.cpp$(ObjectSuffix): wxcrafter_bitmaps.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/wxcrafter_bitmaps.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/wxcrafter_bitmaps.cpp$(DependSuffix) -MM wxcrafter_bitmaps.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Users/mohammadnakhaee/Documents/tbstudio/GUI/wxcrafter_bitmaps.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/wxcrafter_bitmaps.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/wxcrafter_bitmaps.cpp$(PreprocessSuffix): wxcrafter_bitmaps.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/wxcrafter_bitmaps.cpp$(PreprocessSuffix) wxcrafter_bitmaps.cpp

$(IntermediateDirectory)/OrbitalsClass.cpp$(ObjectSuffix): OrbitalsClass.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/OrbitalsClass.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/OrbitalsClass.cpp$(DependSuffix) -MM OrbitalsClass.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Users/mohammadnakhaee/Documents/tbstudio/GUI/OrbitalsClass.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/OrbitalsClass.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/OrbitalsClass.cpp$(PreprocessSuffix): OrbitalsClass.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/OrbitalsClass.cpp$(PreprocessSuffix) OrbitalsClass.cpp

$(IntermediateDirectory)/UnitcellClass.cpp$(ObjectSuffix): UnitcellClass.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/UnitcellClass.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/UnitcellClass.cpp$(DependSuffix) -MM UnitcellClass.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Users/mohammadnakhaee/Documents/tbstudio/GUI/UnitcellClass.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/UnitcellClass.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/UnitcellClass.cpp$(PreprocessSuffix): UnitcellClass.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/UnitcellClass.cpp$(PreprocessSuffix) UnitcellClass.cpp

$(IntermediateDirectory)/SKClass.cpp$(ObjectSuffix): SKClass.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/SKClass.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/SKClass.cpp$(DependSuffix) -MM SKClass.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Users/mohammadnakhaee/Documents/tbstudio/GUI/SKClass.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/SKClass.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/SKClass.cpp$(PreprocessSuffix): SKClass.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/SKClass.cpp$(PreprocessSuffix) SKClass.cpp

$(IntermediateDirectory)/wxcrafter.cpp$(ObjectSuffix): wxcrafter.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/wxcrafter.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/wxcrafter.cpp$(DependSuffix) -MM wxcrafter.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Users/mohammadnakhaee/Documents/tbstudio/GUI/wxcrafter.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/wxcrafter.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/wxcrafter.cpp$(PreprocessSuffix): wxcrafter.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/wxcrafter.cpp$(PreprocessSuffix) wxcrafter.cpp

$(IntermediateDirectory)/ColorsClass.cpp$(ObjectSuffix): ColorsClass.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/ColorsClass.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/ColorsClass.cpp$(DependSuffix) -MM ColorsClass.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Users/mohammadnakhaee/Documents/tbstudio/GUI/ColorsClass.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ColorsClass.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ColorsClass.cpp$(PreprocessSuffix): ColorsClass.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ColorsClass.cpp$(PreprocessSuffix) ColorsClass.cpp

$(IntermediateDirectory)/checktree.cpp$(ObjectSuffix): checktree.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/checktree.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/checktree.cpp$(DependSuffix) -MM checktree.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Users/mohammadnakhaee/Documents/tbstudio/GUI/checktree.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/checktree.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/checktree.cpp$(PreprocessSuffix): checktree.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/checktree.cpp$(PreprocessSuffix) checktree.cpp

$(IntermediateDirectory)/MyMatrix.cpp$(ObjectSuffix): MyMatrix.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/MyMatrix.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/MyMatrix.cpp$(DependSuffix) -MM MyMatrix.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Users/mohammadnakhaee/Documents/tbstudio/GUI/MyMatrix.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/MyMatrix.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/MyMatrix.cpp$(PreprocessSuffix): MyMatrix.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/MyMatrix.cpp$(PreprocessSuffix) MyMatrix.cpp

$(IntermediateDirectory)/sec30TextCtrl.cpp$(ObjectSuffix): sec30TextCtrl.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/sec30TextCtrl.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/sec30TextCtrl.cpp$(DependSuffix) -MM sec30TextCtrl.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Users/mohammadnakhaee/Documents/tbstudio/GUI/sec30TextCtrl.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/sec30TextCtrl.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/sec30TextCtrl.cpp$(PreprocessSuffix): sec30TextCtrl.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/sec30TextCtrl.cpp$(PreprocessSuffix) sec30TextCtrl.cpp

$(IntermediateDirectory)/Sec30.cpp$(ObjectSuffix): Sec30.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Sec30.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Sec30.cpp$(DependSuffix) -MM Sec30.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Users/mohammadnakhaee/Documents/tbstudio/GUI/Sec30.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Sec30.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Sec30.cpp$(PreprocessSuffix): Sec30.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Sec30.cpp$(PreprocessSuffix) Sec30.cpp

$(IntermediateDirectory)/Regression.cpp$(ObjectSuffix): Regression.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Regression.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Regression.cpp$(DependSuffix) -MM Regression.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Users/mohammadnakhaee/Documents/tbstudio/GUI/Regression.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Regression.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Regression.cpp$(PreprocessSuffix): Regression.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Regression.cpp$(PreprocessSuffix) Regression.cpp

$(IntermediateDirectory)/MyFigureClass.cpp$(ObjectSuffix): MyFigureClass.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/MyFigureClass.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/MyFigureClass.cpp$(DependSuffix) -MM MyFigureClass.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Users/mohammadnakhaee/Documents/tbstudio/GUI/MyFigureClass.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/MyFigureClass.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/MyFigureClass.cpp$(PreprocessSuffix): MyFigureClass.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/MyFigureClass.cpp$(PreprocessSuffix) MyFigureClass.cpp

$(IntermediateDirectory)/StructureClass.cpp$(ObjectSuffix): StructureClass.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/StructureClass.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/StructureClass.cpp$(DependSuffix) -MM StructureClass.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Users/mohammadnakhaee/Documents/tbstudio/GUI/StructureClass.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/StructureClass.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/StructureClass.cpp$(PreprocessSuffix): StructureClass.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/StructureClass.cpp$(PreprocessSuffix) StructureClass.cpp

$(IntermediateDirectory)/MainFrame.cpp$(ObjectSuffix): MainFrame.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/MainFrame.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/MainFrame.cpp$(DependSuffix) -MM MainFrame.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Users/mohammadnakhaee/Documents/tbstudio/GUI/MainFrame.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/MainFrame.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/MainFrame.cpp$(PreprocessSuffix): MainFrame.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/MainFrame.cpp$(PreprocessSuffix) MainFrame.cpp

$(IntermediateDirectory)/UpdateClass.cpp$(ObjectSuffix): UpdateClass.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/UpdateClass.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/UpdateClass.cpp$(DependSuffix) -MM UpdateClass.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Users/mohammadnakhaee/Documents/tbstudio/GUI/UpdateClass.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/UpdateClass.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/UpdateClass.cpp$(PreprocessSuffix): UpdateClass.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/UpdateClass.cpp$(PreprocessSuffix) UpdateClass.cpp


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Release/


