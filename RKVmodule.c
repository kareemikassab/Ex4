#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <asm/segment.h>
#include <linux/moduleparam.h>
#include <linux/buffer_head.h>
#include <linux/processor.h>
#include <linux/slab.h>

MODULE_LICENSE("GPL");

struct myfile{
struct file * f;
mm_segment_t fs;
loff_t pos;
};


static char *File= "/proc/version";
static char *reader= "(";



struct myfile * open_file_for_read (char * filename){

	struct myfile *fp= kmalloc(sizeof(struct myfile), GFP_KERNEL);
	fp->fs= get_fs();
	fp->f= filp_open(filename, O_RDONLY,0);
	fp->pos=0;

if(!(fp->f)){
	fp->pos= PTR_ERR(fp->f);
	return 0;
	printk(KERN_INFO "ERROR");
}

	return fp;

}

volatile int read_from_file_until (struct myfile * mf, char * buf, unsigned long vlen, char c){

int ret;
set_fs(get_ds());
ret= vfs_read(mf->f,buf,vlen,&mf->pos);
set_fs(mf->fs);
printk(KERN_INFO "%s\n", buf);
return ret;
}	

void close_file (struct myfile * mf){

	filp_close(mf->f, NULL);

}

static int RKV(void){
struct myfile *RFF;
char *rbuffer2= kmalloc(sizeof(char)*1024, GFP_KERNEL);
memset (rbuffer2,0, sizeof(char)*1024);
RFF= open_file_for_read(File);
read_from_file_until(RFF, rbuffer2, 20, reader);
close_file(RFF);
kfree(rbuffer2);
kfree (RFF);
return 0;
}

static void cleanup(void){
printk(KERN_INFO "\nSUCCESS\n");
}

module_init(RKV);
module_exit(cleanup);

