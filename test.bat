@echo off
make
creditrating.bin test\train01.txt test\test01.txt 20 > test\output01.txt
diff test\output01.txt test\expected01.txt > test\diff01.txt -iw
fc test\diff01.txt test\blank.txt > nul
if not errorlevel 1 (echo TEST PASSED)	else (echo TEST FAILED)

creditrating.bin test\train02.txt test\test02.txt 30 > test\output02.txt
diff test\output02.txt test\expected02.txt > test\diff02.txt -iw
fc test\diff02.txt test\blank.txt > nul
if not errorlevel 1 (echo TEST PASSED)	else (echo TEST FAILED)

creditrating.bin test\train03.txt test\test03.txt 30 > test\output03.txt
diff test\output03.txt test\expected03.txt > test\diff03.txt -iw
fc test\diff03.txt test\blank.txt > nul
if not errorlevel 1 (echo TEST PASSED)	else (echo TEST FAILED)

creditrating.bin test\train04.txt test\test04.txt 40 > test\output04.txt
diff test\output04.txt test\expected04.txt > test\diff04.txt -iw
fc test\diff04.txt test\blank.txt > nul
if not errorlevel 1 (echo TEST PASSED)	else (echo TEST FAILED)

creditrating.bin test\train05.txt test\test05.txt 50 > test\output05.txt
diff test\output05.txt test\expected05.txt > test\diff05.txt -iw
fc test\diff05.txt test\blank.txt > nul
if not errorlevel 1 (echo TEST PASSED)	else (echo TEST FAILED)