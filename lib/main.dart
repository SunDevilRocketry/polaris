import 'package:flutter/cupertino.dart';
import 'package:flutter/widgets.dart';
import 'package:macos_ui/macos_ui.dart';
import 'package:polaris/theme.dart';
import 'package:sfsymbols/sfsymbols.dart';

void main() {
  runApp(const MyApp());
}

class MyApp extends StatelessWidget {
  const MyApp({Key? key}) : super(key: key);

  @override
  Widget build(BuildContext context) {
    return MacosApp(
      title: 'Flutter Demo',
      theme: lightTheme,
      darkTheme: darkTheme,
      home: const MyHomePage(title: 'Flutter Demo Home Page'),
    );
  }
}

class MyHomePage extends StatefulWidget {
  const MyHomePage({Key? key, required this.title}) : super(key: key);
  final String title;

  @override
  State<MyHomePage> createState() => _MyHomePageState();
}

class _MyHomePageState extends State<MyHomePage> {
  int pageIndex = 0;

  @override
  Widget build(BuildContext context) {
    return MacosWindow(
      sidebar: Sidebar(
        minWidth: 200,
        builder: (context, controller) => SidebarItems(
          currentIndex: pageIndex,
          onChanged: (i) => setState(() => pageIndex = i),
          scrollController: controller,
          items: const [
            SidebarItem(
              leading: SFSymbol('house'),
              label: Text('Dashboard'),
            ),
            SidebarItem(
              leading: SFSymbol('house'),
              label: Text('Dashboard'),
            ),
          ],
        ),
      ),
    );
  }
}
