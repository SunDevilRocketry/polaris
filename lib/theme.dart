import 'package:flutter/material.dart' hide ScrollbarThemeData;
import 'package:macos_ui/macos_ui.dart';

MacosThemeData lightTheme = MacosThemeData.light().copyWith(
  visualDensity: VisualDensity.compact,
  canvasColor: MacosColors.appleRed,
);

MacosThemeData darkTheme = MacosThemeData.dark().copyWith(
  visualDensity: VisualDensity.compact,
  scrollbarTheme: const ScrollbarThemeData(
    thumbColor: MacosColors.appleRed,
  ),
);
