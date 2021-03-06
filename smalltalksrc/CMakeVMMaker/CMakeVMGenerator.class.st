"
I am generating a cmake configuration file (CMakeLists.txt)
for building a Squeak Virtual Machine.

Usage: 

CMakeVMGenerator new generate: CogMacOSConfig

or

CMakeVMGenerator new generate: (CogMacOSConfig new setOption: ... ; yourself)

you can provide any valid configuration instead of CogMacOSConfig for build. 

Generator creating a '../build' directory (relative to current one)
and placing config files there.
Also, it expects that appropriate VM (re)sources can be found simplarily:
  ../platforms
  ../src
 but these settings are just default ones and could be changed in config
 (see senders of #topDir #buildDir and #srcDir )

Generator and cmake configs are designed so, that any file-system operations are performed in
<build> directory.
So, if you want to build multiple VMs , using same generated sources, but different configs, you can simply
use different build directories.


"
Class {
	#name : #CMakeVMGenerator,
	#superclass : #CMakeGenerator,
	#instVars : [
		'internalPlugins',
		'externalPlugins',
		'config'
	],
	#category : #CMakeVMMaker
}

{ #category : #'code generation' }
CMakeVMGenerator class >> generate: aConfigOrClass [  
	^self new 
		generate: aConfigOrClass;
		yourself  
]

{ #category : #'as yet unclassified' }
CMakeVMGenerator >> append: aString toAll: list [
	"flatten the list, adding prefix for each element"
	^ list inject: '' into: [:result :each | result, ' ', aString, each ].
]

{ #category : #accessing }
CMakeVMGenerator >> buildDir [
	^ config buildDir
]

{ #category : #accessing }
CMakeVMGenerator >> config [
	^ config
]

{ #category : #accessing }
CMakeVMGenerator >> configurationName [
	^ config class name
]

{ #category : #accessing }
CMakeVMGenerator >> executableName [
	^ 'Squeak'
]

{ #category : #'code generation' }
CMakeVMGenerator >> generate [
	| intPlugins extPlugins |
			
	output := String new writeStream.
	
	config setGlobalOptions: self.
	
	self 
		printHeader;
		project: config executableName.

	config setGlobalOptionsAfterDetermineSystem: self.

	config setupDirectories: self.
	
	self message: '${CMAKE_MODULE_PATH}'.
	self set: 'CMAKE_CONFIGURATION_TYPES' to: 'Release'.

	config preferredIncludes 
		do: [ :each | self includeDirectories: each ].
	self includeDirectories: self includeDirs.	
	config standardIncludes 
		do: [:each | self includeDirectories: each ].

	self addDefinitions: config compilerFlags.

	config extraVMSettings: self.
	
	self puts: 'add_executable(' , config executableName, ' ', config executableType, ' ' , self sources , ')'.
	
	intPlugins := self generatePluginConfigs: config internalPlugins internal: true.
	extPlugins := self generatePluginConfigs: config externalPlugins internal: false.

	self processThirdpartyLibraries.
	
	self processPlugins:  intPlugins, extPlugins.

	config setExtraTargetProperties: self.
	
	self cmd: 'target_link_libraries'
		params: self moduleName , ' ${LINKLIBS}'.

	config postBuildActions: self.
	
	self saveFile.
	self generateBuildScript.
]

{ #category : #'code generation' }
CMakeVMGenerator >> generate: aConfigOrClass [
	
	config := aConfigOrClass isBehavior ifTrue: [ aConfigOrClass new ] ifFalse: [aConfigOrClass].
	^ self generate
]

{ #category : #'build script' }
CMakeVMGenerator >> generateBuildScript [

	(FileStream forceNewFileNamed: (self buildDir / 'build.sh') fullName) nextPutAll: (config fixLineEndsOf: config buildScript); close.
	
]

{ #category : #'as yet unclassified' }
CMakeVMGenerator >> generateExportsH: libs [
	| content |
	content := String streamContents: [:str |
	
		str nextPutAll: '/* This is automatically generated file using CVMMaker on ',
			Date current asString, ' ' , Time current asString , ' */'; cr.
		
		str nextPutAll: 
'extern sqExport vm_exports[];
extern sqExport os_exports[];
'.
		libs do: [:each | 
			str nextPutAll: 'extern sqExport ', each ,'_exports [];'; cr ].
		
		str cr; nextPutAll: 'sqExport *pluginExports[] = {
	vm_exports,
	os_exports,
'.

		libs do: [:each | 
			str nextPutAll:  each ,'_exports,'; cr ].
	
		str nextPutAll: 'NULL
};'

	].

	(FileStream forceNewFileNamed: (self buildDir /'sqNamedPrims.h') fullName) nextPutAll: (config fixLineEndsOf: content); close.
	
]

{ #category : #plugins }
CMakeVMGenerator >> generatePlugin: aPlugin internal: aBoolean extraRules: aBlock [
	" this method called back from plugin"
	^ CMakePluginGenerator new
		generate: aPlugin for: self internal: aBoolean extraRules: aBlock
]

{ #category : #'processing plugins' }
CMakeVMGenerator >> generatePluginConfigs: plugins internal: bool [
	"Answers a collection of CMakePluginGenerator instances"
	
	^ plugins collect: [:each | | plugin |
		plugin := Smalltalk at: each.
		plugin generateFor: self internal: bool.
	].
	

]

{ #category : #'processing plugins' }
CMakeVMGenerator >> generatePluginsSource: plugins internal: bool [

	plugins do: [:each | | plugin gen |
		plugin := Smalltalk at: each.
		gen := plugin generateFor: self internal: bool.
	].
	

]

{ #category : #'sources management' }
CMakeVMGenerator >> includeDirs [

	^ '${crossDir}/vm ${srcVMDir} ${targetPlatform}/vm ${buildDir}'.
]

{ #category : #'as yet unclassified' }
CMakeVMGenerator >> internalPlugins: intList externalPlugins: extList [

	internalPlugins := intList.
	externalPlugins := extList.
]

{ #category : #accessing }
CMakeVMGenerator >> moduleName [ 
	^config executableName
]

{ #category : #accessing }
CMakeVMGenerator >> platformName [
	^ config platformName

]

{ #category : #'processing plugins' }
CMakeVMGenerator >> processExternalPlugins [

	config externalPlugins do: [:each | | plugin gen |
		plugin := Smalltalk at: each.
		gen := plugin generateFor: self internal: false.
		gen doNotGenerate ifFalse: [
			self addSubdirectory: plugin moduleName.
			]
	].
	

]

{ #category : #'processing plugins' }
CMakeVMGenerator >> processInternalPlugins [

	| libs |
	libs := OrderedCollection new.

	config internalPlugins collect: [:each | | plugin gen |
		plugin := Smalltalk at: each.
		gen := plugin generateFor: self internal: true.
		gen doNotGenerate ifFalse: [
			libs add: plugin moduleName.
			self addSubdirectory: plugin moduleName.
			 ].
		].
	
	self cmd: 'target_link_libraries' params:  config executableName , ' ' ,
		(libs inject: '' into: [:res :ea | res, ' ' , ea ]) .

	self generateExportsH: libs.

]

{ #category : #'processing plugins' }
CMakeVMGenerator >> processInternalPlugins: pluginGenerators [

	| libs |
	libs := OrderedCollection new.

	pluginGenerators do: [:gen |
		gen doNotGenerate ifFalse: [
			libs add:  gen plugin moduleName.
			self addSubdirectory:  gen plugin moduleName.
			 ].
		].

	self cmd: 'target_link_libraries' params:  config executableName , ' ' ,
		(libs inject: '' into: [:res :ea | res, ' ' , ea ]) .

	self generateExportsH: libs.

]

{ #category : #'processing plugins' }
CMakeVMGenerator >> processPlugins: pluginGenerators [
	| libs libDeps |

	libs := OrderedCollection new.
	libDeps := Dictionary new.
	pluginGenerators do: [:gen |
		gen doNotGenerate ifFalse: [
			gen isInternal 
				ifTrue: [
					libs add: gen plugin moduleName ]
				ifFalse: [
					"make main module to depend on external plugin, just to make sure it is built 
					 before main module built"
					self 
						cmd: 'add_dependencies' 
						params: config executableName, ' ' , gen plugin moduleName ].
				gen externalDependencies 
					ifNotEmpty: [ :deps |
						libDeps 
							at: gen plugin moduleName
							put: (deps fold: [ :a :b | a, ' ', b ]) ].
			self addSubdirectory: gen plugin moduleName ] ].

	self cmd: 'target_link_libraries' params:  config executableName , ' ' ,
		(libs inject: '' into: [:res :ea | res, ' ' , ea ]).

	libDeps keysAndValuesDo: [ :moduleName :dependencies |
		self 
			cmd: 'add_dependencies' 
			params: moduleName, ' ', dependencies ].  

	self generateExportsH: libs.
]

{ #category : #'as yet unclassified' }
CMakeVMGenerator >> processThirdpartyLibraries [

	config thirdpartyLibs do: [:each |
		each generateFor: self ]


]

{ #category : #accessing }
CMakeVMGenerator >> saveFile [
	
	config write: output contents toFile: (self outputFileName).
	
]

{ #category : #'as yet unclassified' }
CMakeVMGenerator >> setupMacros: gen [
	self config cMakeMacros
		ifNotNil: [ :macros | gen puts: macros ]
]

{ #category : #accessing }
CMakeVMGenerator >> sources [

	self set: #coreSources to: 
		(self append: '${srcVMDir}/' toAll: config coreSources).
		
	self set: #platformVMSources to: 
		(self append: '${targetPlatform}/vm/' toAll: config platformSources).
	
	
	self set: #crossVMSources to: 
		(self append: '${crossDir}/vm/' toAll: config crossSources).
		
	self set: #extraSources to: config extraSources.
	
	^ '${coreSources} ${crossVMSources} ${platformVMSources} ${extraSources}'
]

{ #category : #'as yet unclassified' }
CMakeVMGenerator >> targetPropertyAt: aPropName put: aValue [
	"set target's properties"
	
	self cmd: 'set_property' params: 'TARGET ', config executableName , 
	' PROPERTY ', aPropName , ' ' , aValue.

]

{ #category : #'as yet unclassified' }
CMakeVMGenerator >> targetPropertyAt: aPropName qput: aValue [
	"set target's properties, put value in quotes"
	
	^ self targetPropertyAt: aPropName put: (aValue copyReplaceAll: '"' with: '\"').
]

{ #category : #'thirdparty libs' }
CMakeVMGenerator >> thirdpartyDir [
	^ self buildDir / self thirdpartyDirName
]

{ #category : #'thirdparty libs' }
CMakeVMGenerator >> thirdpartyDirName [
	^ 'thirdParty'
]

{ #category : #accessing }
CMakeVMGenerator >> topDir [
	| dir |
	dir := self config topDir ifNil: [ FileSystem workingDirectory parent ].
	dir isString
		ifTrue: [ ^dir asFileReference ].
	^ dir
]
