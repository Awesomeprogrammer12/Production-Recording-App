# Production-Recording-App
An app for recording Industrial goods high performance built with a C++ Engine in Qt6 and QML  
This is a Qt-based desktop application called
This is a Qt-based desktop application called Zion: Production Records App — a records management system for tracking items with names, numbers, categories, and descriptions.

Key Functionality:
Core Features:

Add Records: Users can add items with name, number (quantity/amount), category, and description
View Records: Displays all records for the current day in a table
Edit Records: Click "EDIT" button to modify existing records
Delete Records: Click "DEL" button to remove records (with confirmation)
Search/Filter: Real-time filtering by name, number, category, or description
Persistent Storage: Saves data to a custom .records file in Documents folder
UI Elements:

Navigation Bar: Tabs for Home, Store, and Stats pages
Home Page: Welcome screen showing recent records
Store Page: Form to add new records + table displaying all records
Settings Dialog: Customize theme (dark/white/cyberpunk/custom), font, and colors
Bottom Bar: Status information and settings button
Additional Features:

Undo/Redo: Ctrl+Z and Ctrl+Y to revert/restore changes
Keyboard Shortcuts: Ctrl+Tab (switch tabs), Alt+Left/Right (snap window), Enter (add record)
Themeing: 4 built-in themes + custom user colors/fonts
Frameless Window: Custom window dragging and resizing from edges
Data Persistence: Loads/saves records organized by date
File Format: Records are stored in a custom text format organized by date:

Code
[YYYY-MM-DD]{
-new
N:"Item Name"
I:"Quantity"
C:"Category"
D:"Description"
T:"Timestamp"
}
It's essentially an inventory/task management app with a polished Qt interface and local file-based storage.
!!Warning this app has live bugs it is under phase 2 of development 
if you want the bugless app with less features contact me 
