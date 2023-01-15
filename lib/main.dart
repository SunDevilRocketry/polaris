import 'package:flutter/cupertino.dart';
import 'package:macos_ui/macos_ui.dart';
import 'package:polaris/pages/analysis/analysis.dart';
import 'package:polaris/pages/configure/configure.dart';
import 'package:polaris/pages/dashboard/dashboard.dart';

void main(List<String> args) => runApp(const App());

class App extends StatelessWidget {
  const App({super.key});

  // This widget is the root of your application.
  @override
  Widget build(BuildContext context) {
    return MacosApp(
      title: 'polaris',
      theme: MacosThemeData.light(),
      darkTheme: MacosThemeData.dark(),
      home: const MainView(),
      debugShowCheckedModeBanner: false,
    );
  }
}

class MainView extends StatefulWidget {
  const MainView({super.key});

  @override
  State<MainView> createState() => _MainViewState();
}

class _MainViewState extends State<MainView> {
  // TODO revert to 0, was changed to 2 to iterate on configuration page.
  int _pageIndex = 2;

  @override
  Widget build(BuildContext context) {
    return MacosWindow(
      sidebar: Sidebar(
        minWidth: 200,
        builder: (context, scrollController) => SidebarItems(
          currentIndex: _pageIndex,
          onChanged: (index) {
            setState(() => _pageIndex = index);
          },
          items: const [
            SidebarItem(
              leading: MacosIcon(CupertinoIcons.rocket_fill),
              label: Text('Dashboard'),
            ),
            SidebarItem(
              leading: MacosIcon(CupertinoIcons.chart_bar_alt_fill),
              label: Text('Analysis'),
            ),
            SidebarItem(
              leading: MacosIcon(CupertinoIcons.gauge),
              label: Text('Configure'),
            ),
          ],
        ),
      ),
      child: IndexedStack(
        index: _pageIndex,
        children: const [
          DashboardPage(),
          AnalysisPage(),
          ConfigurationPage(),
        ],
      ),
    );
  }
}
