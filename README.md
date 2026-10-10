# RogueByte Forensic Recovery Pro (RFRP)

**أداة سطر أوامر للتحقيق الجنائي الرقمي واستعادة الملفات**  
**A command-line tool for digital forensics and file recovery**

- **المطور / Developer:** SidoDev-Dz
- **العلامة التجارية / Brand:** RogueByte
- **الإصدار / Version:** 2.4.0
- **اللغة / Language:** C++20
- **نظام البناء / Build system:** CMake and Ninja
- **الأنظمة / Platforms:** Windows 10/11 x64 and Linux x86-64
- **الترخيص / License:** MIT

## العربية

### المتطلبات

- مترجم C++ يدعم C++20.
- CMake 3.22 أو أحدث، وNinja.
- مكتبة تطوير SQLite3. يدعم المشروع استخدام نسخة SQLite مضمّنة إذا وُجد الملف `third_party/sqlite/sqlite3.c`؛ هذا الملف غير موجود في المستودع الحالي.

### البناء على Windows

افتح PowerShell في مجلد المشروع، ثم نفّذ:

```powershell
cmake --preset windows-x64-release
cmake --build --preset windows-build
ctest --preset windows-test
```

بعد نجاح البناء، شغّل البرنامج من PowerShell لإبقاء رسائله ظاهرة:

```powershell
.\build\windows-release\rfrp_cli.exe
.\build\windows-release\rfrp_cli.exe --test-suite
```

### البناء على Linux

على Ubuntu أو Debian، ثبّت المتطلبات أولًا:

```bash
sudo apt-get update
sudo apt-get install -y cmake ninja-build g++ libsqlite3-dev libssl-dev
```

ثم ابنِ المشروع وشغّل الاختبارات:

```bash
cmake --preset linux-x64-release
cmake --build --preset linux-build
ctest --preset linux-test
```

تشغيل البرنامج:

```bash
./build/linux-release/rfrp_cli
./build/linux-release/rfrp_cli --test-suite
```

### أوامر أداة CLI

| الأمر | الحالة في الإصدار الحالي |
|---|---|
| `rfrp_cli` دون وسائط | يعرض تعليمات الاستخدام ويُنهي البرنامج برمز خروج 1. |
| `rfrp_cli --test-suite` | يعرض رسالة فقط؛ لا يشغّل اختبارات CTest. لتشغيل الاختبارات استخدم `ctest --preset windows-test` أو `ctest --preset linux-test`. |
| `rfrp_cli --hash <مسار-الدليل> [--expected <بصمة-SHA256>]` | صيغة معلنة في تعليمات CLI، لكن تنفيذ الأمر غير متاح في الإصدار الحالي. |
| `rfrp_cli --carve <مسار-الصورة> --out <مجلد-الحفظ> [--aligned]` | صيغة معلنة في تعليمات CLI، لكن تنفيذ الأمر غير متاح في الإصدار الحالي. |
| `rfrp_cli --manifest <معرّف-القضية> --out <manifest.json>` | صيغة معلنة في تعليمات CLI، لكن تنفيذ الأمر غير متاح في الإصدار الحالي. |

أمثلة الصيغ المعلنة للأوامر غير المنفذة بعد (هذه الأمثلة لا تنفّذ العملية في الإصدار الحالي):

```powershell
.\build\windows-release\rfrp_cli.exe --hash "D:\Evidence\disk.dd"
.\build\windows-release\rfrp_cli.exe --hash "D:\Evidence\disk.dd" --expected 0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef
.\build\windows-release\rfrp_cli.exe --carve "D:\Evidence\disk.dd" --out "D:\Evidence\recovered" --aligned
.\build\windows-release\rfrp_cli.exe --manifest CASE-001 --out "D:\Evidence\CASE-001.json"
```

على Linux، استبدل المسارات واستخدم `./build/linux-release/rfrp_cli`.

> **ملاحظة:** النقر المزدوج على ملف CLI قد يفتح نافذة الطرفية ثم يغلقها فور انتهاء البرنامج. شغّله من PowerShell أو Terminal لرؤية المخرجات. البناء الحالي لا ينشئ واجهة رسومية.

## English

### Requirements

- A C++ compiler with C++20 support.
- CMake 3.22 or newer and Ninja.
- The SQLite3 development library. The project can use its embedded SQLite amalgamation if `third_party/sqlite/sqlite3.c` is present; that file is not included in the current repository.

### Build on Windows

Open PowerShell in the project directory and run:

```powershell
cmake --preset windows-x64-release
cmake --build --preset windows-build
ctest --preset windows-test
```

After a successful build, run the CLI from PowerShell to keep its output visible:

```powershell
.\build\windows-release\rfrp_cli.exe
.\build\windows-release\rfrp_cli.exe --test-suite
```

### Build on Linux

On Ubuntu or Debian, install the prerequisites:

```bash
sudo apt-get update
sudo apt-get install -y cmake ninja-build g++ libsqlite3-dev libssl-dev
```

Configure, build, and run the tests:

```bash
cmake --preset linux-x64-release
cmake --build --preset linux-build
ctest --preset linux-test
```

Run the CLI:

```bash
./build/linux-release/rfrp_cli
./build/linux-release/rfrp_cli --test-suite
```

### CLI commands

| Command | Status in the current release |
|---|---|
| `rfrp_cli` with no arguments | Prints usage instructions and exits with status 1. |
| `rfrp_cli --test-suite` | Prints a message only; it does not run CTest. Run `ctest --preset windows-test` or `ctest --preset linux-test` to execute the tests. |
| `rfrp_cli --hash <evidence-path> [--expected <sha256>]` | Listed in the CLI usage text, but not implemented in the current release. |
| `rfrp_cli --carve <image-path> --out <destination> [--aligned]` | Listed in the CLI usage text, but not implemented in the current release. |
| `rfrp_cli --manifest <case-id> --out <manifest.json>` | Listed in the CLI usage text, but not implemented in the current release. |

Examples of the advertised but currently unimplemented command syntax (these examples do not perform the requested operations):

```powershell
.\build\windows-release\rfrp_cli.exe --hash "D:\Evidence\disk.dd"
.\build\windows-release\rfrp_cli.exe --hash "D:\Evidence\disk.dd" --expected 0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef
.\build\windows-release\rfrp_cli.exe --carve "D:\Evidence\disk.dd" --out "D:\Evidence\recovered" --aligned
.\build\windows-release\rfrp_cli.exe --manifest CASE-001 --out "D:\Evidence\CASE-001.json"
```

On Linux, substitute your evidence paths and use `./build/linux-release/rfrp_cli`.

> **Note:** Double-clicking a CLI executable may open and immediately close its console when the program exits. Run it from PowerShell or a terminal to see its output. The current build does not produce a graphical application.

## License / الترخيص

MIT License - Copyright (c) 2026 RogueByte / SidoDev-Dz
