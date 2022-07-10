int8_t xdir2;
int8_t ydir2;


/* Calculate absolute position of screen */
void calc_xy_abs()
{
    scr_x_cr = scr_x;
    scr_x += xdir2;
    // if (xdir2 & 0b1000000) {
    //     scr_x += xdir2
    // } else {
    //     scr_x -= xdir2
    // }

    scr_y_cr = scr_y;
    scr_x += xdir2;
    // if (ydir2 & 0b1000000) {
    //     scr_y += ydir2;
    // } else {
    //     scr_y -= ydir2;
    // }
}


/* */
inline void calc_x_rel()
{
    if (!timer) {
        // detect change direction?
        if (tmp_x_pos & 0b1000000) {
            tmp_x_pos &= 0xf;
            offset_x = tmp_x_pos;
            x_pos = tmp_x_pos;
            goto y;
        }
    }
    x_pos = (scr_x + offset_x) & 0xf;
y:
    if (!timer) {
        // detect change direction?
        if (tmp_y_pos & 0b1000000) {
            tmp_y_pos &= 0xf;
            offset_y = tmp_y_pos;
            y_pos = tmp_y_pos;
        }
    }
    y_pos = (scr_y + offset_y) & 0xf;
}


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
        calc_xy_abs();
        calc_xy_rel();

        split_screen()

    while (1);
}
