import 'dart:io';

import 'package:flutter/cupertino.dart';
import 'package:macos_ui/macos_ui.dart';
import 'package:polaris/linux/polaris_linux_app.dart';
import 'package:polaris/macos/pages/dashboard.dart';
import 'package:polaris/windows/polaris_windows_app.dart';
import 'package:sfsymbols/sfsymbols.dart';

void main() {
  runApp(const PolarisApp());
}

class PolarisApp extends StatelessWidget {
  const PolarisApp({Key? key}) : super(key: key);

  // This widget is the root of your application.
  @override
  Widget build(BuildContext context) {
    if (Platform.isMacOS) {
      return MacosApp(
        theme: MacosThemeData.light(),
        darkTheme: MacosThemeData.dark(),
        title: 'Polaris',
        home: const Home(),
      );
    } else if (Platform.isWindows) {
      return const WindowsApp();
    } else {
      return const LinuxApp();
    }
  }
}

class Home extends StatefulWidget {
  const Home({Key? key}) : super(key: key);

  @override
  _HomeState createState() => _HomeState();
}

class _HomeState extends State<Home> {
  int pageIndex = 0;

  final List<Widget> pages = [const Dashboard()];

  Color textLuminance(Color backgroundColor) {
    return backgroundColor.computeLuminance() > 0.5
        ? CupertinoColors.black
        : CupertinoColors.white;
  }

  @override
  Widget build(BuildContext context) {
    return MacosWindow(
      child: IndexedStack(
        index: pageIndex,
        children: pages,
      ),
      sidebar: Sidebar(
        minWidth: 200,
        builder: (context, controller) {
          return SidebarItems(
            currentIndex: pageIndex,
            onChanged: (i) => setState(() => pageIndex = i),
            scrollController: controller,
            items: const [
              SidebarItem(
                leading: SFSymbol('house'),
                label: Text('Dashboard'),
              ),
            ],
          );
        },
      ),
    );
  }
}
