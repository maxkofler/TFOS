extern void kernel_main();

/// This is just a launchpad to the Rust code
void kernel_entry(void)
{
    kernel_main();
    while (1)
    {
    }
}