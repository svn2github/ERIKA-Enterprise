#
# make_signature.mk
#

# This file is included by the makedist makefile and specifies the
# actions that have to be taken to generate the signature of the various libraries

MYSIG = >> ee_$(DIST)/signature/signature.xml


make_signature: ee_$(DIST)/signature/signature.xml
	@echo signature up2date.


ee_$(DIST)/signature/signature.xml: \
		config/conf.mk \
		ee_$(DIST) \
		config/make_signature.mk
	@echo Generating ee_$(DIST)/signature/signature.xml...
	@rm -f ee_$(DIST)/signature/signature.xml
	@mkdir -p ee_$(DIST)/signature
	@echo "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"             $(MYSIG)
	@echo "<!DOCTYPE DISTRIBUTIONS SYSTEM \"EE_Signature.dtd\">"   $(MYSIG)
	@echo "<DISTRIBUTIONS>"                                        $(MYSIG)
	@$(foreach c, $($(DIST)), make --no-print-directory -C . make_signature_distribution_$(c); )
	@echo "</DISTRIBUTIONS>"                                        $(MYSIG)



make_signature_distribution_%:
	@echo "  <DISTRIBUTION Name=\""$*"\" Library=\"ee_"$*"\">"      $(MYSIG); \
	if test $($*_DESCRIPTION);                                             \
			then (echo "    <DESCRIPTION>"$($*_DESCRIPTION)"</DESCRIPTION>" $(MYSIG)); \
		fi;                                                            \
	for x in $($*); do                                                     \
	                  echo "    <OPTION Name=\""$${x}"\"/>"      $(MYSIG); \
                          done;                                                \
	$(foreach s,$(ALL_SYMBOLS_MULTICORE),                                      \
		(if test $($*_$(s));                                           \
			then (echo "    <SYMBOL Name=\""EE_$(s)"\" Value=\""$($*_$(s))"\" />" $(MYSIG)); \
		fi) &&                                                         \
	) true;                                                                \
	echo "  </DISTRIBUTION>"                                     $(MYSIG);

