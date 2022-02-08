#
# Wait for boot message "BOOT COMPLETED"
#

proc wait_boot {{cmd ""}} {
  if { [ catch {string first "BOOT COMPLETED" [get_screen]} err ] } {
    after time 5 [list wait_boot $cmd]
  } elseif {[string first "BOOT COMPLETED" [get_screen]] >= 0} {
    message "*match*"
    $cmd
  } elseif {$cmd != ""} {
    after time 5 [list wait_boot $cmd]
  }
}

proc done {} {
  global speed
  message "Finished!"
  set speed 100
}

#set renderer none
machine msx2plus
ext ram4mb
ext ide

set power off
diskmanipulator create hd.dsk 32M 32M
hda hd.dsk
diskmanipulator format hda1 hda2
diskmanipulator import hda1 [glob -type f A/*]
diskmanipulator import hda2 [glob -type f B/*]
message "hd.dsk created"
set power on

# Speed up boot
set save_settings_on_exit off
set fullspeedwhenloading on
set speed 9999

message "Detecting boot..."
wait_boot done
