module.exports = function(grunt) {

  // Project configuration.
  grunt.initConfig({
    pkg: grunt.file.readJSON('package.json'),
    gyp: {
		configure: {
			command: 'configure',
		},
		build: {
			command: 'build',
		}
	},
	mochaTest: {
		test: {
			src: ['test/*.js']
		}
	},
	watch: {
		binding: {
			files: ['binding.gyp'],
			tasks: ['gyp:configure', 'gyp:build', 'test'],
		},
		addon: {
			files: ['src/*.cc'],
			tasks: ['gyp:build', 'test'],
		},
		test: {
			files: ['test/*.js'],
			tasks: ['test']
		}
	},
  });

	grunt.loadNpmTasks('grunt-node-gyp');
	grunt.loadNpmTasks('grunt-contrib-watch');
	grunt.loadNpmTasks('grunt-mocha-test');
	grunt.registerTask('test', ['mochaTest']);
	grunt.registerTask('default', ['gyp:configure', 'gyp:build', 'test']);
};