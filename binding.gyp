{
	"targets" : [
		{
			"target_name": "delib",
			"sources": ["src/delib.cc"],			
			"include_dirs": [
				"$(DELIB64_INCLUDE)"
			],
			"libraries": [
				"-l$(DELIB64_LIB)/delib64.lib"
			]
		}
	],
}