import 'package:fluent_ui/fluent_ui.dart';

class WindowsApp extends StatelessWidget {
  const WindowsApp({Key? key}) : super(key: key);

  @override
  Widget build(BuildContext context) {
    return FluentApp(
      title: 'Polaris',
      initialRoute: '/',
      routes: {'/': (_) => const HomePage()},
    );
  }
}

class HomePage extends StatelessWidget {
  const HomePage({Key? key}) : super(key: key);

  @override
  Widget build(BuildContext context) {
    return Container();
  }
}
