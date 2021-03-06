Extension { #name : #TParseNode }

{ #category : #'*vmmakerjs' }
TParseNode >> emitJSCodeAsArgumentOn: aStream level: level generator: aCodeGen [
	^self emitJSCodeOn: aStream level: level generator: aCodeGen
]

{ #category : #'*vmmakerjs' }
TParseNode >> emitJSCodeAsExpressionOn: aStream level: level generator: aCodeGen [
	^self emitJSCodeOn: aStream level: level generator: aCodeGen
]

{ #category : #'*vmmakerjs' }
TParseNode >> emitJSCodeOn: aStream level: lev generator: gen [
	self subclassResponsibility.
]

{ #category : #'*vmmakerjs' }
TParseNode >> emitJSCommentOn: aStream level: level [
	"Emit the transferred Smalltalk comments as C comments."

	comment ifNotNil: [
		comment isString ifTrue: [^self].	"safety catch"
		aStream cr.
		1 to: comment size do: [:index | 
			aStream 
				tab: level;
				nextPutAll: '/* ';
				nextPutAll: (comment at: index);
				nextPutAll: ' */';
				cr].
		aStream cr]
]

{ #category : #'*vmmakerjs' }
TParseNode >> isBitBltPtr [
	^false
]

{ #category : #'*vmmakerjs' }
TParseNode >> isConstantNull [
	^false
]

{ #category : #'*vmmakerjs' }
TParseNode >> isConstantZero [
	^false
]

{ #category : #'*vmmakerjs' }
TParseNode >> isEqualityTest [
	^false
]

{ #category : #'*vmmakerjs' }
TParseNode >> isInterpreterProxyConstant [
	^false
]

{ #category : #'*vmmakerjs' }
TParseNode >> isLeafOrFunc [
	^self isLeaf
]

{ #category : #'*vmmakerjs' }
TParseNode >> isPlusOne [
	^false
]

{ #category : #'*vmmakerjs' }
TParseNode >> isTimesFour [
	^false
]
