
int main()
{
    ; load grfx at 4000h
    if (!load_vram("./blk4.sr5", 0x0, 0x8000)) {
        printf("Error reading grfx files\n$");
        exit(1);
    }
    printf("Reading grfx files\n$");

    if (!load_vram("./px.sc5", 0x8000, 0x8000)) {
        printf("Error reading parallax grfx files\n$");
        exit(2);
    }
    printf("Reading parallax files\n$");

    if (!load_vram("./barra.sr5", (256+192)*128, 64*128)) {
        printf("Error reading infobar files\n$");
        exit(3);
    }
    printf("Reading parallax files\n$");

    if (!load_ram("./stg3.fnd", 0x8000)) {
        printf("Error reading level files\n$");
        exit(4);
    }
    printf("Reading level files\n$");

    set_scr5(SPRITES_16x16);
    set_color(0, 0, 0);
    set_palette();

    read_sreg(2); // status register 2

    init_isr2(2, 158); // actually 160

    // main loop
    do {

        
        split_screen()
        
    while (1);
}
