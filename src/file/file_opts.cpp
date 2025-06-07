
#include "file_opts.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#ifdef _WIN32
typedef unsigned int uint;
#endif

namespace Rhizar16 {

char * FileOptions::load_file(const char * path) {

   FILE * fptr = fopen(path,"r");

   if (fptr == NULL) {
      internal_status = NO_FILE;
      return NULL;
   }

   int res_len = 64;
   int res_pos = 0;
   char * res = (char *)malloc(sizeof(char)*64);

   if (res == NULL) {
      internal_status = NO_MEM;
      return NULL;
   }


   int c;
   while ( (c = fgetc(fptr)) != EOF) {

      res[res_pos] = c;
      res_pos += 1;

      if (res_pos == res_len) {

         res = (char *)realloc(res,sizeof(char)*res_len*2);
         if (res == NULL) {
            internal_status = NO_MEM;
            return NULL;
         }

         res_len *= 2;
      }

   }

   res[res_pos] = '\0';

   res = (char *)realloc(res,sizeof(char)*(res_pos+1));

   internal_status = SUCCESS;
   fclose(fptr);
   return res;
}

void FileOptions::load_ini(std::string path) {
   static char def[4] = "INI";

   char * file = load_file(path.c_str());
   load_file_type = def;

   if (file == NULL)
      return;

   char * fpos = file;

   int mode = 0;
   int prevmode;
   char * mark;

   int rownum = 1;
   int colnum = 1;

   struct FileSection * curr_section = NULL;
   struct FileKV * curr_keyvalue = NULL;

   while (*fpos != '\0') {

      switch (mode) {

         /* start mode */
         case 0:
            if (*fpos == '[' && colnum == 1) {
               mark = fpos + 1;
               mode = 1;
            }
            else if (isspace(*fpos))
               break;
            else if (*fpos == ';' ||
                     *fpos == '#') {
               prevmode = 0;
               mode = 2;
            }
            else {
               internal_status = BAD_FORMAT;
               goto finally;
            }
            break;

         /* section header mode */
         case 1:
            if (*fpos == ']') {
               uint hsize = fpos - mark;

               curr_section = (struct FileSection *)malloc(sizeof(struct FileSection));
               if (curr_section == NULL) {
                  internal_status = NO_MEM;
                  goto finally;
               }
               memset(curr_section,0,sizeof(struct FileSection));

               curr_section->name = (char *)malloc(sizeof(char)*hsize+sizeof('\0'));
               if (curr_section->name == NULL) {
                  internal_status = NO_MEM;
                  free(curr_section);
                  curr_section = NULL;
                  goto finally;
               }

               memcpy(curr_section->name,mark,hsize);
               curr_section->name[hsize] = '\0';

               mode = 3;
            }
            else if (isprint(*fpos))
               break;
            else {
               internal_status = BAD_FORMAT;
               goto finally;
            }
            break;

         /* comment mode */
         case 2:
            if (*fpos == '\n')
               mode = prevmode;
            break;
         
         /* section mode */
         case 3:
            if (isspace(*fpos))
               break;
            else if (*fpos == ';' ||
                     *fpos == '#') {
               prevmode = 3;
               mode = 2;
            }
            else if (*fpos == '[' && colnum == 1) {
               mark = fpos + 1;
               mode = 1;
               curr_section->next = sections;
               sections = curr_section;
               curr_section = NULL;
            }
            else if (isprint(*fpos) && colnum == 1) {
               mark = fpos;
               mode = 4;
            }
            else {
               internal_status = BAD_FORMAT;
               goto finally;
            }
            break;

         /* key mode */
         case 4:
            if (*fpos == '=') {
               char * vend = fpos - 1;
               while (isspace(*vend)) --vend;
               uint ksize = (vend - mark) + 1;

               curr_keyvalue = (struct FileKV *)malloc(sizeof(struct FileKV));
               if (curr_keyvalue == NULL) {
                  internal_status = NO_MEM;
                  goto finally;
               }
               memset(curr_keyvalue,0,sizeof(struct FileKV));

               curr_keyvalue->key = (char *)malloc(sizeof(char)*ksize + sizeof('\0'));
               if (curr_keyvalue->key == NULL) {
                  internal_status = NO_MEM;
                  free(curr_keyvalue);
                  curr_keyvalue = NULL;
                  goto finally;
               }

               memcpy(curr_keyvalue->key,mark,ksize);
               curr_keyvalue->key[ksize] = '\0';

               mark = fpos + 1;
               mode = 5;
            }
            else if (*fpos == ';' ||
                     *fpos == '#') {
               internal_status = BAD_FORMAT;
               goto finally;
            }
            else if (isprint(*fpos) || isspace(*fpos)) {
               break;
            }
            else {
               internal_status = BAD_FORMAT;
               goto finally;
            }
            break;

         /* val mode */
         case 5:
            if (*fpos == ';' ||
                *fpos == '#') {
               prevmode = 3;
               mode = 2;

collect_value:
               while (isspace(*mark)) ++mark;
               if (*mark == '"') ++mark;

               char * vend = fpos - 1;
               while (isspace(*vend)) --vend;
               if (*vend == '"') --vend;

               uint vsize = (vend - mark) + 1;

               if ((int)vsize <= 0)
                  vsize = 1;

               curr_keyvalue->val = (char *)malloc(sizeof(char)*vsize + sizeof('\0'));
               if (curr_keyvalue->val == NULL) {
                  internal_status = NO_MEM;
                  free(curr_keyvalue->key);
                  free(curr_keyvalue);
                  curr_keyvalue = NULL;
                  goto finally;
               }

               memcpy(curr_keyvalue->val,mark,vsize);
               curr_keyvalue->val[vsize] = '\0';

               curr_keyvalue->next = curr_section->data;
               curr_section->data = curr_keyvalue;
               curr_keyvalue = NULL;
            }
            else if (*fpos == '\n') {
               mode = 3;
               goto collect_value;
            }
            else if (isprint(*fpos) || isspace(*fpos))
               break;
            else {
               internal_status = BAD_FORMAT;
               goto finally;
            }
            break;
      }

      if (*fpos == '\n') {
         rownum += 1;
         colnum = 0;
      }
      colnum += 1;
      fpos += 1;
   }

   if (mode == 1 || mode == 4 || mode == 5)
      internal_status = BAD_FORMAT;

   if (mode == 3) {
      curr_section->next = sections;
      sections = curr_section;
      curr_section = NULL;
   }

finally:
   if (internal_status == BAD_FORMAT)
      format_error_pos = std::pair<int,int>{rownum,colnum};
   else
      format_error_pos = std::pair<int,int>{0,0};
   if (curr_section) {
      while (curr_section->data) {
         struct FileKV * to_free = curr_section->data;
         curr_section->data = curr_section->data->next;
         free(to_free->key);
         free(to_free->val);
         free(to_free);
      }
      free(curr_section->name);
      free(curr_section);
   }
   if (curr_keyvalue) {
      free(curr_keyvalue->key);
      free(curr_keyvalue->val);
      free(curr_keyvalue);
   }
   free(file);
}

void FileOptions::load_json(std::string path) {
   static char def[5] = "JSON";

   char * file = load_file(path.c_str());
   load_file_type = def;

   if (file == NULL)
      return;

   char * fpos = file;

   int mode = 0;
   char * mark;

   int rownum = 1;
   int colnum = 1;

   struct FileSection * curr_section = NULL;
   struct FileKV * curr_keyvalue = NULL;

   while (*fpos != '\0') {

      switch (mode) {

         /* start mode */
         case 0:
            if (*fpos == '{')
               mode = 1;
            else if (isspace(*fpos))
               break;
            else {
               internal_status = BAD_FORMAT;
               goto finally;
            }
            break;

         /* between section mode */
         case 1:
            if (*fpos == '"') {
               mark = fpos + 1;
               mode = 2;
            }
            else if (*fpos == '}')
               mode = 9;
            else if (isspace(*fpos))
               break;
            else {
               internal_status = BAD_FORMAT;
               goto finally;
            }
            break;

         /* section title mode */
         case 2:
            if (*fpos == '"') {
               uint hsize = fpos - mark;

               curr_section = (struct FileSection *)malloc(sizeof(struct FileSection));
               if (curr_section == NULL) {
                  internal_status = NO_MEM;
                  goto finally;
               }
               memset(curr_section,0,sizeof(struct FileSection));

               curr_section->name = (char *)malloc(sizeof(char)*hsize+sizeof('\0'));
               if (curr_section->name == NULL) {
                  internal_status = NO_MEM;
                  free(curr_section);
                  goto finally;
               }

               memcpy(curr_section->name,mark,hsize);
               curr_section->name[hsize] = '\0';

               mode = 3;
            }
            else if (isprint(*fpos))
               break;
            else {
               internal_status = BAD_FORMAT;
               goto finally;
            }
            break;

         /* section colon mode */
         case 3:
            if (*fpos == ':')
               mode = 4;
            else {
               internal_status = BAD_FORMAT;
               goto finally;
            }
            break;

         /* section between-keyvalue mode */
         case 4:
            if (*fpos == '{')
               mode = 5;
            else if (isspace(*fpos))
               break;
            else {
               internal_status = BAD_FORMAT;
               goto finally;
            }
            break;

         /* between-keyvalue mode */
         case 5:
            if (*fpos == '"') {
               mark = fpos + 1;
               mode = 6;
            }
            else if (*fpos == '}') {
               mode = 7;
               curr_section->next = sections;
               sections = curr_section;
               curr_section = NULL;
            }
            else if (isspace(*fpos))
               break;
            else {
               internal_status = BAD_FORMAT;
               goto finally;
            }
            break;

         /* key mode */
         case 6:
            if (*fpos == '"') {
               uint ksize = fpos - mark;

               curr_keyvalue = (struct FileKV *)malloc(sizeof(struct FileKV));
               if (curr_keyvalue == NULL) {
                  internal_status = NO_MEM;
                  goto finally;
               }
               memset(curr_keyvalue,0,sizeof(struct FileKV));

               curr_keyvalue->key = (char *)malloc(sizeof(char)*ksize + sizeof('\0'));
               if (curr_keyvalue->key == NULL) {
                  internal_status = NO_MEM;
                  free(curr_keyvalue);
                  curr_keyvalue = NULL;
                  goto finally;
               }

               memcpy(curr_keyvalue->key,mark,ksize);
               curr_keyvalue->key[ksize] = '\0';

               mode = 8;

            }
            else if (isprint(*fpos))
               break;
            else {
               internal_status = BAD_FORMAT;
               goto finally;
            }
            break;

         /* between section before comma mode */
         case 7:
            if (*fpos == ',')
               mode = 1;
            else if (isspace(*fpos))
               break;
            else if (*fpos == '}')
               mode = 9;
            else {
               internal_status = BAD_FORMAT;
               goto finally;
            }
            break;

         /* key colon mode */
         case 8:
            if (*fpos == ':') {
               mode = 10;
               mark = fpos + 1;
            }
            else {
               internal_status = BAD_FORMAT;
               goto finally;
            }
            break;

         /* end mode */
         case 9:
            if (isspace(*fpos))
               break;
            else {
               internal_status = BAD_FORMAT;
               goto finally;
            }
            break;

         /* value mode */
         case 10:
            if (*fpos == ',' || *fpos == '}') {

               mode = 5;

               while (isspace(*mark)) ++mark;
               if (*mark == '"') ++mark;

               char * vend = fpos - 1;
               while (isspace(*vend)) --vend;
               if (*vend == '"') --vend;

               uint vsize = (vend - mark) + 1;

               curr_keyvalue->val = (char *)malloc(sizeof(char)*vsize + sizeof('\0'));
               if (curr_keyvalue->val == NULL) {
                  internal_status = NO_MEM;
                  free(curr_keyvalue->key);
                  free(curr_keyvalue);
                  curr_keyvalue = NULL;
                  goto finally;
               }

               memcpy(curr_keyvalue->val,mark,vsize);
               curr_keyvalue->val[vsize] = '\0';

               curr_keyvalue->next = curr_section->data;
               curr_section->data = curr_keyvalue;
               curr_keyvalue = NULL;

               if (strchr(curr_section->data->val,'"')) {
                  internal_status = BAD_FORMAT;
                  goto finally;
               }
            }
            if (*fpos == '}') {

               mode = 7;

               curr_section->next = sections;
               sections = curr_section;
               curr_section = NULL;
            }
            else if (isprint(*fpos) || isspace(*fpos))
               break;
            else {
               internal_status = BAD_FORMAT;
               goto finally;
            }
            break;

      }

      if (*fpos == '\n') {
         rownum += 1;
         colnum = 0;
      }
      colnum += 1;
      fpos += 1;
   }

   if (mode != 9 && mode != 0)
      internal_status = BAD_FORMAT;


finally:
   if (internal_status == BAD_FORMAT)
      format_error_pos = std::pair<int,int>{rownum,colnum};
   else
      format_error_pos = std::pair<int,int>{0,0};
   if (curr_section) {
      while (curr_section->data) {
         struct FileKV * to_free = curr_section->data;
         curr_section->data = curr_section->data->next;
         free(to_free->key);
         free(to_free->val);
         free(to_free);
      }
      free(curr_section->name);
      free(curr_section);
   }
   if (curr_keyvalue) {
      free(curr_keyvalue->key);
      free(curr_keyvalue->val);
      free(curr_keyvalue);
   }
   free(file);
}

void FileOptions::load(std::string path, Format format) {

   unload_sections();

   internal_status = SUCCESS;

   switch (format) {
      case INI:
         load_ini(path);
         break;
      case JSON:
         load_json(path);
         break;
      default:
      case AUTOMATIC:
         if (path.rfind(__RHIZAR16_FILE_EXTENSION_INI__) + strlen(__RHIZAR16_FILE_EXTENSION_INI__) == path.length())
            load_ini(path);
         else if (path.rfind(__RHIZAR16_FILE_EXTENSION_JSON__) + strlen(__RHIZAR16_FILE_EXTENSION_JSON__) == path.length())
            load_json(path);
         else
            load_ini(path);
         break;
   }

   if (internal_status != SUCCESS)
      unload_sections();
   else
      reverse_order();

}

void FileOptions::reverse_order() {

   struct FileSection * interm_section, * new_section_head = NULL, * curr_section = sections;
   struct FileKV * interm_keyvalue, * new_keyvalue_head, * curr_keyvalue;

   while (curr_section) {

      interm_section = curr_section;

      new_keyvalue_head = NULL;
      curr_keyvalue = curr_section->data;

      curr_section = curr_section->next;
      interm_section->next = new_section_head;
      new_section_head = interm_section;

      while (curr_keyvalue) {

         interm_keyvalue = curr_keyvalue;
         curr_keyvalue = curr_keyvalue->next;

         interm_keyvalue->next = new_keyvalue_head;
         new_keyvalue_head = interm_keyvalue;

      }

      interm_section->data = new_keyvalue_head;
   }

   sections = new_section_head;
}

void FileOptions::save_ini(std::string path) {

   FILE * fptr;
   if (std::string("-") == path)
      fptr = stdout;
   else
      fptr = fopen(path.c_str(),"w");

   if (fptr == NULL) {
      internal_status = NO_FILE;
      return;
   }

   struct FileSection * curr_section;
   struct FileKV * curr_keyvalue;

   fprintf(fptr,"\n");

   curr_section = sections;
   while (curr_section) {

      fprintf(fptr,"[%s]\n",curr_section->name);

      curr_keyvalue = curr_section->data;
      while (curr_keyvalue) {

         fprintf(fptr,"%s=\"%s\"\n",curr_keyvalue->key,curr_keyvalue->val);

         curr_keyvalue = curr_keyvalue->next;
      }

      fprintf(fptr,"\n");
      curr_section = curr_section->next;
   }

   if (fptr != stdout)
      fclose(fptr);
   internal_status = SUCCESS;
}

void FileOptions::save_json(std::string path) {

   FILE * fptr;
   if (std::string("-") == path)
      fptr = stdout;
   else
      fptr = fopen(path.c_str(),"w");

   if (fptr == NULL) {
      internal_status = NO_FILE;
      return;
   }

   struct FileSection * curr_section;
   struct FileKV * curr_keyvalue;

   fprintf(fptr,"\n");
   fprintf(fptr,"{\n");

   curr_section = sections;
   while (curr_section) {

      fprintf(fptr,"  \"%s\": {\n",curr_section->name);

      curr_keyvalue = curr_section->data;
      while (curr_keyvalue) {

         fprintf(fptr,"    \"%s\": \"%s\",\n",curr_keyvalue->key,curr_keyvalue->val);

         curr_keyvalue = curr_keyvalue->next;
      }

      fprintf(fptr,"  },\n");

      curr_section = curr_section->next;
   }

   fprintf(fptr,"}\n");

   if (fptr != stdout)
      fclose(fptr);
   internal_status = SUCCESS;
}

void FileOptions::save(std::string path, Format format) {

   internal_status = SUCCESS;

   if (sections == NULL) {
      internal_status = NO_FILE;
      return;
   }

   switch (format) {
      case INI:
         save_ini(path);
         break;
      case JSON:
         save_json(path);
         break;
      default:
      case AUTOMATIC:
         if (path.rfind(__RHIZAR16_FILE_EXTENSION_INI__) + strlen(__RHIZAR16_FILE_EXTENSION_INI__) == path.length())
            save_ini(path);
         else if (path.rfind(__RHIZAR16_FILE_EXTENSION_JSON__) + strlen(__RHIZAR16_FILE_EXTENSION_JSON__) == path.length())
            save_json(path);
         else
            save_ini(path);
         break;
   }

}

void FileOptions::unload_sections() {

   struct FileSection * curr_section, * to_free_section;
   struct FileKV * curr_keyvalue, * to_free_keyvalue;

   curr_section = sections;

   while (curr_section) {

      curr_keyvalue = curr_section->data;

      while (curr_keyvalue) {

         to_free_keyvalue = curr_keyvalue;
         curr_keyvalue = curr_keyvalue->next;

         free(to_free_keyvalue->key);
         free(to_free_keyvalue->val);
         free(to_free_keyvalue);
      }

      to_free_section = curr_section;
      curr_section = curr_section->next;

      free(to_free_section->name);
      free(to_free_section);
   }

   sections = NULL;
}

FileOptions::FileOptions() {
}

FileOptions::FileOptions(std::string path, Format format) {
   load(path,format);
}

FileOptions::~FileOptions() {
   unload_sections();
}

FileOptions::Status FileOptions::status() {
   return internal_status;
}

std::pair<int,int> FileOptions::err_pos() {
   return format_error_pos;
}

std::string FileOptions::fformat() {
   if (load_file_type == NULL)
      return std::string("");
   return std::string(load_file_type);
}

long FileOptions::getopt_int(std::string section, std::string key) {

   const char * str_section = section.c_str();
   const char * str_key = key.c_str();

   struct FileSection * curr_section;
   struct FileKV * curr_keyvalue;

   curr_section = sections;

   internal_status = NO_SECTION;

   while (curr_section) {

      if (strcmp(str_section,curr_section->name) == 0) {

         if (internal_status == NO_SECTION)
            internal_status = NO_KEY;

         curr_keyvalue = curr_section->data;

         while (curr_keyvalue) {

            if (strcmp(str_key,curr_keyvalue->key) == 0) {

               errno = 0;
               char * endpos;
               long res = strtol(curr_keyvalue->val,&endpos,0);
               if (errno || curr_keyvalue->val == endpos)
                  internal_status = WRONG_DATATYPE;
               else {
                  internal_status = SUCCESS;
                  return res;
               }
            }

            curr_keyvalue = curr_keyvalue->next;
         }
      }

      curr_section = curr_section->next;
   }

   return 0;
}

double FileOptions::getopt_flt(std::string section, std::string key) {

   const char * str_section = section.c_str();
   const char * str_key = key.c_str();

   struct FileSection * curr_section;
   struct FileKV * curr_keyvalue;

   curr_section = sections;

   internal_status = NO_SECTION;

   while (curr_section) {

      if (strcmp(str_section,curr_section->name) == 0) {

         if (internal_status == NO_SECTION)
            internal_status = NO_KEY;

         curr_keyvalue = curr_section->data;

         while (curr_keyvalue) {

            if (strcmp(str_key,curr_keyvalue->key) == 0) {

               errno = 0;
               char * endpos;
               double res = strtod(curr_keyvalue->val,&endpos);
               if (errno || curr_keyvalue->val == endpos)
                  internal_status = WRONG_DATATYPE;
               else {
                  internal_status = SUCCESS;
                  return res;
               }
            }

            curr_keyvalue = curr_keyvalue->next;
         }
      }

      curr_section = curr_section->next;
   }

   return 0;
}

std::string FileOptions::getopt_str(std::string section, std::string key) {

   const char * str_section = section.c_str();
   const char * str_key = key.c_str();

   struct FileSection * curr_section;
   struct FileKV * curr_keyvalue;

   curr_section = sections;

   internal_status = NO_SECTION;

   while (curr_section) {

      if (strcmp(str_section,curr_section->name) == 0) {

         if (internal_status == NO_SECTION)
            internal_status = NO_KEY;

         curr_keyvalue = curr_section->data;

         while (curr_keyvalue) {

            if (strcmp(str_key,curr_keyvalue->key) == 0) {

               internal_status = SUCCESS;

               return std::string(curr_keyvalue->val);

            }

            curr_keyvalue = curr_keyvalue->next;
         }
      }

      curr_section = curr_section->next;
   }

   return std::string();
}

bool FileOptions::has_section(std::string section) {

   internal_status = SUCCESS;

   const char * str_section = section.c_str();

   struct FileSection * curr_section = sections;

   while (curr_section) {

      if (strcmp(str_section,curr_section->name) == 0)
         return true;

      curr_section = curr_section->next;
   }

   internal_status = NO_SECTION;
   return false;
}

bool FileOptions::has_key(std::string section, std::string key) {
   
   const char * str_section = section.c_str();
   const char * str_key = key.c_str();

   struct FileSection * curr_section;
   struct FileKV * curr_keyvalue;

   curr_section = sections;

   internal_status = NO_SECTION;

   while (curr_section) {

      if (strcmp(str_section,curr_section->name) == 0) {

         if (internal_status == NO_SECTION)
            internal_status = NO_KEY;

         curr_keyvalue = curr_section->data;

         while (curr_keyvalue) {

            if (strcmp(str_key,curr_keyvalue->key) == 0) {

               internal_status = SUCCESS;

               return true;

            }

            curr_keyvalue = curr_keyvalue->next;
         }
      }

      curr_section = curr_section->next;
   }

   return false;
}

std::string FileOptions::perror(std::string head) {

   switch (internal_status) {
      case SUCCESS:
         return head + ": success";
         break;
      case NO_FILE:
         return head + ": no file found, file empty";
         break;
      case BAD_FORMAT:
         {
            char buf[2048];
            snprintf(buf,2048,": formatting error while parsing %s file; row: %d, col: %d",
                    fformat().c_str(),std::get<0>(format_error_pos),std::get<1>(format_error_pos));
            return head + std::string(buf);
         }
         break;
      case WRONG_DATATYPE:
         return head + ": reqeusted datatype does not match value";
         break;
      case NO_SECTION:
         return head + ": no matching section found";
         break;
      case NO_KEY:
         return head + ": no matching key found";
         break;
      case NO_MEM:
         return head + ": out of memory";
         break;
   }

   return head + ": unknown status";
}

void FileOptions::collect_sections(std::vector<std::string> & container) {

   internal_status = SUCCESS;

   struct FileSection * curr_section = sections;

   while (curr_section) {

      container.push_back(std::string(curr_section->name));

      curr_section = curr_section->next;
   }
}

void FileOptions::collect_keys(std::string section, std::vector<std::string> & container) {

   internal_status = NO_SECTION;

   struct FileSection * curr_section = sections;

   while (curr_section) {

      if (strcmp(curr_section->name,section.c_str()) == 0) {

         internal_status = SUCCESS;

         struct FileKV * curr_keyvalue = curr_section->data;

         while (curr_keyvalue) {

            container.push_back(std::string(curr_keyvalue->key));

            curr_keyvalue = curr_keyvalue->next;
         }
      }

      curr_section = curr_section->next;
   }
}

}
