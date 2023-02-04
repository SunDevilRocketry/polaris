import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';
import 'package:macos_ui/macos_ui.dart';
import 'package:syncfusion_flutter_charts/charts.dart';

class TelemetryPage extends StatelessWidget {
  const TelemetryPage({super.key});

  @override
  Widget build(BuildContext context) {
    return Builder(
      builder: (context) {
        return MacosScaffold(
          toolBar: ToolBar(
            title: const Text('Altimeter'),
            padding: const EdgeInsets.fromLTRB(20, 0, 20, 0),
            actions: [
              ToolBarPullDownButton(
                label: "Actions",
                tooltipMessage: "File",
                icon: CupertinoIcons.ellipsis_circle,
                items: [
                  MacosPulldownMenuItem(
                    label: "New Simulation",
                    title: const Text("New Simulation"),
                    onTap: () => debugPrint("Starting new sim..."),
                  ),
                  MacosPulldownMenuItem(
                    label: "Open",
                    title: const Text("Open"),
                    onTap: () => debugPrint("Opening..."),
                  ),
                  MacosPulldownMenuItem(
                    label: "Save",
                    title: const Text("Save"),
                    onTap: () => debugPrint("Saving Sim..."),
                  ),
                  MacosPulldownMenuItem(
                    label: "Save As",
                    title: const Text("Save As"),
                    onTap: () => debugPrint("Saving As..."),
                  ),
                ],
              ),
              ToolBarIconButton(
                label: 'Comm Port',
                icon: const MacosIcon(CupertinoIcons.link_circle),
                showLabel: false,
                tooltipMessage: "Comm Port",
                onPressed: () {
                  debugPrint("Comm Port");
                },
              ),
              ToolBarIconButton(
                label: 'Aquire Data',
                icon: const MacosIcon(CupertinoIcons.arrow_down_circle),
                showLabel: false,
                tooltipMessage: "Aquire Data",
                onPressed: () {
                  debugPrint("Aquiring Data");
                },
              ),
              ToolBarIconButton(
                label: 'Toggle Sidebar',
                icon: const MacosIcon(CupertinoIcons.sidebar_left),
                showLabel: false,
                tooltipMessage: 'Toggle Sidebar',
                onPressed: () {
                  MacosWindowScope.of(context).toggleSidebar();
                },
              ),
            ],
          ),
          children: [
            ContentArea(
              builder: (context, scrollController) {
                return SafeArea(
                  child: Padding(
                    padding: const EdgeInsets.all(10.0),
                    child: Scaffold(
                      body: SfCartesianChart(),
                    ),
                  ),
                );
              },
            ),
            ResizablePane(
              builder: (context, scrollController) {
                return Column(
                  children: <Widget>[
                    SizedBox(
                      width: double.infinity,
                      child: RichText(
                        textAlign: TextAlign.center,
                        text: const TextSpan(
                          text: "Setup",
                          style: TextStyle(fontSize: 25),
                        ),
                      ),
                    ),
                    const Divider(
                      color: Color.fromARGB(94, 158, 158, 158),
                      thickness: 1,
                    ),
                    const Text("Main: "),
                    const MacosTextField(
                      placeholder: "Main",
                    ),
                    const Text("Drogue: "),
                    const MacosTextField(
                      placeholder: "Drogue",
                    ),
                    const Spacer(),
                    const Divider(
                      color: Color.fromARGB(94, 158, 158, 158),
                      thickness: 1,
                    ),
                    const Text(
                      "Statistics",
                      style: TextStyle(fontSize: 30),
                    ),
                    Padding(
                      padding: const EdgeInsets.fromLTRB(20, 10, 20, 20),
                      child: SizedBox(
                        width: double.infinity,
                        child: RichText(
                          text: TextSpan(
                            style: DefaultTextStyle.of(context).style,
                            children: const <TextSpan>[
                              TextSpan(
                                  text: "Apogee: \n",
                                  style: TextStyle(fontSize: 18)),
                              TextSpan(
                                  text: "Time: \n",
                                  style: TextStyle(fontSize: 18)),
                              TextSpan(
                                  text: "\nMain Deploy\n",
                                  style: TextStyle(fontSize: 23)),
                              TextSpan(
                                  text: "Altitude: \n",
                                  style: TextStyle(fontSize: 18)),
                              TextSpan(
                                  text: "Time: \n",
                                  style: TextStyle(fontSize: 18)),
                              TextSpan(
                                  text: "\nDrogue Deploy \n",
                                  style: TextStyle(fontSize: 23)),
                              TextSpan(
                                  text: "Altitude: \n",
                                  style: TextStyle(fontSize: 18)),
                              TextSpan(
                                  text: "Time:",
                                  style: TextStyle(fontSize: 18)),
                            ],
                          ),
                        ),
                      ),
                    ),
                    Padding(
                      padding: const EdgeInsets.all(10),
                      child: SizedBox(
                        height: 50,
                        width: double.infinity,
                        child: PushButton(
                          buttonSize: ButtonSize.large,
                          color: Colors.blue,
                          onPressed: () {
                            debugPrint("Running Simulation...");
                          },
                          child: const Text(
                            "Run Simulation",
                            style: TextStyle(fontSize: 20),
                          ),
                        ),
                      ),
                    ),
                  ],
                );
              },
              minWidth: 300,
              resizableSide: ResizableSide.left,
              startWidth: 300,
              maxWidth: 300,
              isResizable: true,
            ),
          ],
        );
      },
    );
  }
}
