import 'package:flutter/cupertino.dart';
import 'package:macos_ui/macos_ui.dart';
import 'package:sfsymbols/sfsymbols.dart';

class Dashboard extends StatelessWidget {
  const Dashboard({Key? key}) : super(key: key);

  @override
  Widget build(BuildContext context) {
    return MacosScaffold(
      titleBar: TitleBar(
        title: const Text('Polaris'),
        centerTitle: false,
        actions: [
          MacosIconButton(
            backgroundColor: MacosColors.transparent,
            icon: const SFSymbol(
              'sidebar.left',
              palette: SymbolColorPalette(MacosColors.systemGrayColor),
            ),
            onPressed: () {
              MacosWindowScope.of(context).toggleSidebar();
            },
          ),
          const SizedBox(width: 10),
        ],
      ),
    );
  }
}
