#!/usr/bin/perl
# =========================================================================
# ==
# == Version  : 1.0
# ==
# == Function : 
# ==
# == Argument : do perl warning.pl [-e] [-h]
# ==
# =========================================================================
# ==
# == Historic
# ==
# ==  16/04/13 : Creation
# ==
# =========================================================================
# == $Header:   P:/VE_S97/LOG/70_SubProject/Archives/S97_SWA_BSW/warning.plv   1.2   21 Mar 2014 15:28:00   xfeng  $
# =========================================================================
local $| = 1;

$Echo              = "";
$Help              = "";
$Folder            = ".\\";                                            ##arg
$CsvFolder         = ".\\";                                            ##arg
$warning_file_name = "warning.csv";                                    ##arg
$warn_file_ext     = "warn";                                           ##arg
$warn_split        = "\n";                                             ##arg

# =========================================================================

if ($#ARGV == -1)
{
#    $ARGV[0] = "-h";
}

for ($index=0;$index<$#ARGV +1 ;$index++)
{
   if (  (uc("@ARGV[$index]") eq "-H")
      || (uc("@ARGV[$index]") eq "/H")
      || (uc("@ARGV[$index]") eq "-?")
      || (uc("@ARGV[$index]") eq "/?"))
   {
     $Help = @ARGV[$index];
   }
   elsif (uc("@ARGV[$index]") eq "-E")
   {
      $Echo = uc("@ARGV[$index]");
   }
   elsif (uc("@ARGV[$index]") eq "-S")
   {
      $Folder = @ARGV[$index+1];
   }
   elsif (uc("@ARGV[$index]") eq "-D")
   {
      $CsvFolder = @ARGV[$index+1];
   }
   elsif (uc("@ARGV[$index]") eq "-F")
   {
      $warning_file_name = @ARGV[$index+1];
   }
   elsif (lc("@ARGV[$index]") eq "-warnext")
   {
      $warn_file_ext = @ARGV[$index+1];
   }
   elsif (lc("@ARGV[$index]") eq "-warnsplit")
   {
      $warn_split = @ARGV[$index+1];
   }
}

# =========================================================================
if ($Help)
{
   #======================================================================
   $displayHelp = $displayHelp."\n=============== WARNING HELP =================== \n";
   $displayHelp = $displayHelp."-- [-h] : Display this comment \n";
   $displayHelp = $displayHelp."-- [-e] : Display mode \n";
   $displayHelp = $displayHelp."-- [-s] : Source code Directory \n";
   $displayHelp = $displayHelp."-- [-d] : Warning file Directory \n";
   $displayHelp = $displayHelp."-- [-f] : Warning file name (default:$warning_file_name)\n";
   $displayHelp = $displayHelp."-- [-warnext] : Warn file extention (default:$warn_file_ext)\n";
   $displayHelp = $displayHelp."-- [-warnsplit] : Warn file splt char (default:\\n) \n";
   $displayHelp = $displayHelp."======================================================== \n";
   print STDOUT $displayHelp;
   #======================================================================
   exit();
}
else
{   
   #=================================================================================================
   print STDOUT ("\nWarning analysis\n\n");

   #=================================================================================================
   #begin
   # Cat all warning
   $Warning = `cat $Folder/*.$warn_file_ext`;

   if ($warn_split ne "\n")
   {
      $Warning =~ s/\n//sg;
      $Warning =~ s/$warn_split/\n/sg;
   }
   $Warning =~ s/;//sg;
   $Warning =~ s/[ ]+/ /sg;

   @WarningArray = split("\n",$Warning);
   foreach my $MyWarning (@WarningArray) 
   {
      if ($MyWarning =~ /(\w+\.\w+):(\d+)\:(\d+):(.*)/ )
      {
         if ($4 ne "")
         {
            $arg1 = $1;
            $arg2 = $2;
            $arg3 = "($3)$4";
            $arg3 =~ s/\"//sg;
            $Warning_HashTable{"$arg1;$arg2;$arg3"} = "$arg1;$arg2;$arg3;";
          }
      }
   }

   #=================================================================================================
   # Load reference CSV file

   open(CSV_IN, "<$CsvFolder\\$warning_file_name");
   $file = join('',<CSV_IN>);
   close(CSV_IN);
   @WarningArray    = split("\n",$file);
   @WarningArray[0] = '';

   # Separate justified and non-justified warnings
   foreach my $MyWarning (@WarningArray) 
   {
      if ($MyWarning =~ /^([^;]*);([^;]*);([^;]*);[ \t]*([^;]*)[ \t]*;([^;]*)$/)
      {
         if ($4 ne '')
         {
            $Warning_HashTableCsv{"$1;$2;$3"} = "$1;$2;$3;$4;removed_item";
         }
         else
         {
            $Warning_HashTableCsv{"$1;$2;$3"} = "$1;$2;$3;$4;to_be_deleted";
         }
      }
   }

   #=================================================================================================
   # Update CSV 

   # Update CSV warnings with warnings from the software generation
   foreach my $MyWarning (sort keys %Warning_HashTable) 
   {
      if (exists($Warning_HashTableCsv{$MyWarning}))
      {
         # Warning already exists: Remove "removed_item" or "to_be_deleted"
         $Warning_HashTableCsv{$MyWarning} =~ s/[^;]+$//;
      }
      else
      {
         # New warning: add warning with tag "new_item"
         $Warning_HashTableCsv{$MyWarning} = "$Warning_HashTable{$MyWarning};new_item";
      }
   }
   # Remove old CSV warnings that were not justified
   foreach my $MyWarning (sort keys %Warning_HashTableCsv) 
   {
      if ($Warning_HashTableCsv{$MyWarning} =~ /^[^;]*;[^;]*;[^;]*;[^;]*;to_be_deleted$/)
      {
         delete($Warning_HashTableCsv{$MyWarning});
      }
   }

   #=================================================================================================
   # Load and edit CSV file

   $csv_file        = "FILE_NAME;LINE;WARNING;JUSTIFICATION;REMOVED/NEW;\n";
   $display  = '';

   # Get the list of unjustified warnings
   foreach my $MyWarning (sort keys %Warning_HashTableCsv) 
   {
      $csv_file =  $csv_file."$Warning_HashTableCsv{$MyWarning}\n";

      if ($Warning_HashTableCsv{$MyWarning} =~ /^([^;]*);([^;]*);([^;]*);[ \t]*;([^;]*)$/)
      {
         $display         = $display."$MyWarning\n";
      }
   }

   if ($file ne $csv_file)
   {
      open(CSV_OUT, ">$CsvFolder\\$warning_file_name");
      print CSV_OUT ("$csv_file");
      close(CSV_OUT);
   }
   if ($display ne '')
   {
      print STDOUT ("=====================================================================================\n");
      print STDOUT ("The following warnings must be justified.                                            \n");
      print STDOUT ("=====================================================================================\n");
      print STDOUT ("$display\n");
      print STDOUT ("\n=====================================================================================\n");
      print STDOUT ("Update $CsvFolder\\$warning_file_name                                                \n");
      print STDOUT ("=====================================================================================\n");
      print STDOUT ("\nYou can update $CsvFolder\\$warning_file_name.\n\n");
   }

   print STDOUT ("End of Warning analysis\n");
   #=================================================================================================
}


##=================================================================================================
#
