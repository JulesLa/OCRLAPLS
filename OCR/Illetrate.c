#include<gtk/gtk.h>
#include<stdio.h>
#include<stdlib.h>
#include<gdk-pixbuf/gdk-pixbuf.h>
#include "ocr.h"

//void gtk_main_quit(GtkWidget *widget, gpointer pData);
void file_select();
void recognize();
void file_save();

static GtkWidget *window;
static GtkWidget *image;
static GdkPixbuf *pixbuf;
static GtkWidget *imgbox;
static gchar* filename;


int main(int argc, char *argv[]){
	
	GtkBuilder	*builder;

	GtkWidget *addButton;
	GtkWidget *recognizebutton;
	GtkWidget *savebutton;
	
	gtk_init(&argc, &argv);
	
	builder = gtk_builder_new();

	gtk_builder_add_from_file(builder,"Illetrate.ui" , NULL);

	
	window =GTK_WIDGET(gtk_builder_get_object(builder,"window1"));
	imgbox = GTK_WIDGET(gtk_builder_get_object(builder,"imgbox"));
	addButton = GTK_WIDGET(gtk_builder_get_object(builder,"AddButton"));
	recognizebutton = GTK_WIDGET(gtk_builder_get_object(builder,"Recognize")); 
	savebutton = GTK_WIDGET(gtk_builder_get_object(builder,"savebutton"));

	g_signal_connect(G_OBJECT(addButton),"clicked",G_CALLBACK(file_select),NULL);
	g_signal_connect(G_OBJECT(recognizebutton),"clicked",G_CALLBACK(recognize),NULL);
	g_signal_connect(G_OBJECT(savebutton),"clicked",G_CALLBACK(file_save),NULL);

	g_object_unref(builder);

	gtk_widget_show_all(GTK_WIDGET(window));


	gtk_main();

}



void file_select(){
	GtkWidget *dialog;
	GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
	gint res;

	dialog = gtk_file_chooser_dialog_new ("Open File",
                                      GTK_WINDOW(window),
                                      action,
                                      ("Cancel"),
                                      GTK_RESPONSE_CANCEL,
                                      ("Open"),
                                      GTK_RESPONSE_ACCEPT,
                                      NULL);

	res = gtk_dialog_run (GTK_DIALOG (dialog));
	if (res == GTK_RESPONSE_ACCEPT)
  {
    GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
    filename = gtk_file_chooser_get_filename (chooser);
		if (image)
			gtk_image_set_from_file(GTK_IMAGE(image),filename);
			
		else
		{
			pixbuf = gdk_pixbuf_new_from_file((char*)filename,NULL);
			pixbuf = gdk_pixbuf_scale_simple(pixbuf,400,400,GDK_INTERP_BILINEAR);
			image = gtk_image_new_from_pixbuf(pixbuf);
		
			gtk_box_pack_start(GTK_BOX(imgbox),image,FALSE,FALSE,5);
		
			gtk_widget_show(image);
		}
  }

gtk_widget_destroy (dialog);
}


void recognize(){
	g_message("\nfilename : %s",(char*)filename);
  OCR((char *)filename);
  /*FILE *file = fopen(filename,"r");
  char string[4096];

  GtkTextBuffer * buffer = gtk_text_view_get_buffer(text_view);
  int i = 0;
  GtkTextIter iter;
  gtk_text_buffer_get_end_iter(buffer,&iter);
  while(fgets(string,4096,file) != NULL)
  {
    i += 1;
    gtk_text_buffer_insert(buffer, &iter,string, -1);
  }
  fclose(file);*/
}

void file_save(){
	GtkWidget *dialog;
	GtkFileChooser *chooser;
	GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_SAVE;
	gint res;

	dialog = gtk_file_chooser_dialog_new ("Save File",
                                      GTK_WINDOW(window),
                                      action,
                                      "Cancel",
                                      GTK_RESPONSE_CANCEL,
                                      "Save",
                                      GTK_RESPONSE_ACCEPT,
                                      NULL);
	chooser = GTK_FILE_CHOOSER (dialog);

	gtk_file_chooser_set_do_overwrite_confirmation (chooser, TRUE);


res = gtk_dialog_run (GTK_DIALOG (dialog));
if (res == GTK_RESPONSE_ACCEPT)
  {
		
    char *filesave;

    filesave = gtk_file_chooser_get_filename (chooser);
    //save_to_file (filename);
		FILE *fichier = fopen(filesave,"w");
		FILE *ocr = fopen("result.ocr","r");
		
		if(fichier == NULL)
		{
			g_message("Le fichier de sauvegarde n'est pas crée\n");
			return;
		}
		if(ocr == NULL)
		{
			g_message("Le fichier result.ocr n'existe pas\n");
			return;
		}
		
		int c;

		while((c = fgetc(ocr)) != EOF)
		{
			fputc(c,fichier);
		}

		g_message("%s",filesave);
    g_free (filesave);
  	fclose(fichier);
		fclose(ocr);
	}

gtk_widget_destroy (dialog);
}
