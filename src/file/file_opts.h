
#ifndef __RHIZAR16_FILE_OPTS__

#define __RHIZAR16_FILE_OPTS__

#define __RHIZAR16_FILE_EXTENSION_INI__    ".ini"
#define __RHIZAR16_FILE_EXTENSION_JSON__   ".json"

#include <string>
#include <utility>
#include <vector>

namespace Rhizar16 {

/* reads in a file on initialization or via method call
 * and allows for the user to query specific fields and
 * options. This simplifies the normally kind of annoying
 * problem of digging through files for various arguments */
class FileOptions {
public:

   enum Format {
      INI,
      JSON,
      /* attempt to discover the format via the 
       * file extension, default to INI if this fails */
      AUTOMATIC
   };

   enum Status {
      SUCCESS,
      NO_FILE,
      BAD_FORMAT,
      WRONG_DATATYPE,
      NO_SECTION,
      NO_KEY,
      NO_MEM,
   };

private:

   /* attempt to load an ini formatted file */
   void load_ini(std::string path);
   /* attempt to load a json formatted file */
   void load_json(std::string path);

   /* attempt to save the held data in an ini formatted file */
   void save_ini(std::string path);
   /* attempt to save the held data in a json formatted file */
   void save_json(std::string path);

   char * load_file(const char * path);

   void unload_sections();
   void reverse_order();

   struct FileKV {
      char * key;
      char * val;
      struct FileKV * next;
   };

   struct FileSection {
      char * name;
      struct FileSection * next;
      struct FileKV * data;
   };

   struct FileSection * sections = NULL;

   /* holds the status of the class. This is useful for
    * seeing if file loading/parsing proceeded correctly */
   Status internal_status = SUCCESS;
   /* holds the file position of the format error if BAD_FORMAT
    * was the status following any of the load_* methods. Will
    * be cleared the next time a load_* method is called.    
    * Format is { 0 = row, 1 = column }                       */
   std::pair<int,int> format_error_pos{0,0};
   char * load_file_type = NULL;

public:

   FileOptions();
   FileOptions(std::string path, Format format = AUTOMATIC);

   ~FileOptions();

   /* load the given file with the provided format */
   void load(std::string path, Format format = AUTOMATIC);

   /* save the stored options to the given path using
    * the provided format.
    * Note: if "-" is given as the path, the file is
    * output is sent to stdout instead of a file.    */
   void save(std::string path, Format format = AUTOMATIC);

   long getopt_int(std::string section, std::string key);
   double getopt_flt(std::string section, std::string key);
   std::string getopt_str(std::string section, std::string key);

   bool has_section(std::string section);
   bool has_key(std::string section, std::string key);

   Status status();
   std::pair<int,int> err_pos();
   std::string fformat();
   std::string perror(std::string head = "FileOptions");

   /* place all loaded sections in the passed container. The container
    * is not cleared internally, and should be cleared by the calling
    * process if nessesary.                                             */
   void collect_sections(std::vector<std::string> & container);

   /* place all loaded keys from the given section in the passed 
    * container. The container is not cleared internally, and
    * should be cleared by the calling process if nessesary.            */
   void collect_keys(std::string section, std::vector<std::string> & container);
};

}


#endif
