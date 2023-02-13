import 'package:flutter/cupertino.dart';
import 'package:macos_ui/macos_ui.dart';

class ConfigurationPage extends StatelessWidget {
  const ConfigurationPage({super.key});

  @override
  Widget build(BuildContext context) {
    return Builder(
      builder: (context) {
        return MacosScaffold(
          toolBar: ToolBar(
            title: const Text('Telemetry'),
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
                return const Center(child: Slider());
              },
            ),
          ],
        );
      },
    );
  }
}

class Slider extends StatefulWidget {
  const Slider({Key? key}) : super(key: key);

  @override
  State<Slider> createState() => _SliderState();
}

class _SliderState extends State<Slider> {
  double _value = 0.0;

  @override
  Widget build(BuildContext context) {
    return Row(
      children: [
        Text(
          _value.truncate().toString(),
          style: CupertinoTheme.of(context).textTheme.textStyle.copyWith(
                fontSize: 12,
              ),
        ),
        MacosSlider(
          value: _value,
          onChanged: (newValue) => {setState(() => _value = newValue)},
          max: 300,
        )
      ],
    );
  }
}
