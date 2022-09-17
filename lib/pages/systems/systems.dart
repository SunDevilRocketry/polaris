import 'package:flutter/cupertino.dart';
import 'package:macos_ui/macos_ui.dart';

class SystemsPage extends StatelessWidget {
  const SystemsPage({super.key});

  @override
  Widget build(BuildContext context) {
    return Builder(
      builder: (context) {
        return MacosScaffold(
          toolBar: ToolBar(
            title: const Text('Systems'),
            actions: [
              ToolBarIconButton(
                label: 'Toggle Sidebar',
                icon: const MacosIcon(CupertinoIcons.sidebar_left),
                showLabel: false,
                tooltipMessage: 'Toggle Sidebar',
                onPressed: () {
                  MacosWindowScope.of(context).toggleSidebar();
                },
              )
            ],
          ),
          children: [
            ContentArea(
              builder: (context, scrollController) {
                return const Center(
                  child: Text('Systems'),
                );
              },
            ),
          ],
        );
      },
    );
  }
}
