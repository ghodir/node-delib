var delib = require('../');
var expect = require('chai').expect;
var exec = require('child_process').exec;

var module = delib.RO_USB;

describe('DELIB node wrapper', function() {
	it('should be able to open a module', function() {
		var m = delib.openModule(module, 0);
		expect(m).to.be.ok;
	});
	
	it('should be able to get delib version', function() {
		var version = delib.getDELIBVersion();
		expect(version).to.be.ok;
	});
	
	it('should be able to close the previously opened module', function() {
		var m = delib.openModule(module, 0);
		expect(m).to.be.ok;
		delib.closeModule(m);
	});
	
	it('should be able to return the last error code', function() {
		var m = delib.openModule(module, 0);
		expect(delib.getLastError()).to.equal(0);
		var m = delib.openModule(module + 1, 0);
		expect(delib.getLastError()).to.equal(delib.ERR_DEVICE_NOT_FOUND);
	});
	
	it('should return a proper error string for the last error', function() {
		var m = delib.openModule(module + 1, 0);
		expect(delib.getLastError()).to.equal(delib.ERR_DEVICE_NOT_FOUND);
		expect(delib.getLastErrorText()).to.be.a('string');
	});
	
	describe('Analog Inputs', function() {
		beforeEach(function() {
			this.module = delib.openModule(module, 0);
			expect(this.module).to.be.ok;
		});
		
		afterEach(function() {
			delib.closeModule(this.module);
		});
		
		it('should be able to set the analog input mode', function() {
			delib.adSetMode(this.module, 0, delib.ADDA_MODE_UNIPOL_10V);
			expect(delib.adGetMode(this.module, 0)).to.equal(delib.ADDA_MODE_UNIPOL_10V);
		});
		
		it('should read voltage from ad', function() {
			delib.adSetMode(this.module, 0, delib.ADDA_MODE_UNIPOL_10V);
			var value = delib.adGetVolt(this.module, 0);
			expect(value).to.be.a('number');
		});
	});
	
	describe('Analog Outputs', function() {
		beforeEach(function() {
			this.module = delib.openModule(module, 0);
			expect(this.module).to.be.ok;
		});
		
		afterEach(function() {
			delib.closeModule(this.module);
		});
		
		it('should be able to set the analog output mode', function() {
			/**
			 * Not supported by RO_USB
			 
			delib.daSetMode(this.module, 0, delib.ADDA_MODE_UNIPOL_2V5);
			expect(delib.daGetMode(this.module, 0)).to.equal(delib.ADDA_MODE_UNIPOL_2V5);
			*/
			
			delib.daSetMode(this.module, 0, delib.ADDA_MODE_UNIPOL_5V);
			expect(delib.daGetMode(this.module, 0)).to.equal(delib.ADDA_MODE_UNIPOL_5V);
			
			delib.daSetMode(this.module, 0, delib.ADDA_MODE_UNIPOL_10V);
			expect(delib.daGetMode(this.module, 0)).to.equal(delib.ADDA_MODE_UNIPOL_10V);
		});
	});
});
