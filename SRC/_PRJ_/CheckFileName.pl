#!/usr/bin/perl
# =========================================================================
# ==
# == Function :
# ==
# == Argument : 
# ==
# =========================================================================
# ==
# == Historic
# ==
# ==  30/05/12 : 
# ==
# =========================================================================
# == $Header:   P:/VE_S97/LOG/70_SubProject/Archives/S97_SWA_BSW/CheckFileName.plv   1.3   13 Jun 2013 16:11:48   vbecquet  $
# =========================================================================
local $| = 1;

$Option    = "";
$OptionArg = "";
$Folder    = ".";

if ($#ARGV == -1)
{
    $ARGV[0] = "-h";
}

for ($index=0;$index<$#ARGV +1 ;$index++)
{
    if (lc($ARGV[$index]) eq "-f")
    {
        $Option = $ARGV[$index];
        $OptionArg = $ARGV[++$index];
    }
    elsif (lc($ARGV[$index]) eq "-mk")
    {
        $Option = $ARGV[$index];
        $OptionArg = $ARGV[++$index];
    }
    elsif (lc($ARGV[$index]) eq "-l")
    {
        $Option = $ARGV[$index];
        $OptionArg = $ARGV[++$index];
    }
    elsif (lc($ARGV[$index]) eq "-dir")
    {
        $Option = $ARGV[$index];
        $OptionArg = $ARGV[++$index];
    }
    elsif ((lc($ARGV[$index]) eq "-h") || (lc($ARGV[$index]) eq "/h")
       || ($ARGV[$index] eq "-?")   || ($ARGV[$index] eq "?")
       || ($ARGV[$index] eq "-?"))
    {
        # ==========================================================================
        # =  Help Section
        # ==========================================================================
        print STDOUT "\n================ CheckFileName HELP ======================== \n";
        print STDOUT "-- Usage   : CheckFileName [-f file] [-mk makefile]\n";
        print STDOUT "-- Options :[-f]   : source file\n";
        print STDOUT "--          [-mk]  : makefile (exemple: obj.mk\n";
        print STDOUT "--          [-l]   : list (exemple: LIST_STD\n";
        print STDOUT "--          [-dir] : sources files directory\n";
        print STDOUT "--          [-h]   : echo this help screen \n";
        print STDOUT "\n============================================================\n";
        #===========================================================================
        exit();
    }
}
#=====================================================================================
# Check the source files name and include header mane 
#=====================================================================================
print STDOUT ("\nCheck the source files name and include header mane\n\n");
$check_ok = 1;
$counter  = 0;

if ($Option eq "-mk")
{
    open(SRC_FILE,"<$OptionArg");
    while (<SRC_FILE>)
    {
       if ($_ =~ /.*\:(.*)/)
       {
          @SrcFileArray = split(/\s/, $1);
          foreach $file (@SrcFileArray)
          {
             $FileArray_List{uc($file)} = "$file";
          }
       }
    }
    close(SRC_FILE);
}
elsif ($Option eq "-l")
{
    open(SRC_FILE,"<$OptionArg");
    while (<SRC_FILE>)
    {
       $file = $_;
       chomp($file);
       $FileArray_List{uc($file)} = "$file";
    }
    close(SRC_FILE);
}

elsif ($Option eq "-f")
{
    $file = $OptionArg;
    $FileArray_List{uc($file)} = "$file";
}
elsif ($Option eq "-dir")
{
    $Folder = $OptionArg;
    $src_file_list = `dir \/B $Folder\\*.c`.`dir \/B $Folder\\*.h`.`dir \/B $Folder\\*.asm`.`dir \/B $Folder\\*.inc 2>nul`;
    @SrcFileArray = split("\n",$src_file_list);
    foreach $file (@SrcFileArray)
    {
       $FileArray_List{uc($file)} = "$file";
    }
}

#=====================================================================================
# Files list in directory
#=====================================================================================

$src_file_list = `dir \/B $Folder\\*.c`.`dir \/B $Folder\\*.h`.`dir \/B $Folder\\*.asm`.`dir \/B $Folder\\*.inc 2>nul`;
@SrcFileArray = split("\n",$src_file_list);
foreach $file (@SrcFileArray)
{
   $FileArray_Dir{uc($file)} = "$file";
}

#=====================================================================================
# 
#=====================================================================================

$src_file = "";
foreach my $file_name (sort keys %FileArray_List) 
{
   open(SRC,"< $Folder/$FileArray_List{$file_name}") or die "cannot open < $Folder/$FileArray_List{$file_name}: $!";
   $src_file = $src_file.join('',<SRC>);
   close(SRC);
}

$src_file =~ s/\/\*(.*?)\*\///sg;
$src_file =~ s/\/\/[^\n]*\n/\n/sg;
$src_file =~ s/\n+/\n/sg;
$src_file =~ s/^\n//sg;
$src_file =~ s/\t/ /sg;

@SrcFileArray = split("\n",$src_file);
foreach $line (@SrcFileArray)
{
  if ($line =~ /\#include[\s]*[\"\<](.*)[\"\>]/)
  {
    $file = $1;
    if ($FileArray_Include{uc($file)} eq "")
    {
       $FileArray_Include{uc($file)} = "$file";
    }
    elsif ($FileArray_Include{uc($file)} ne "$file")
    {
       print("Warning: difference between #include\"$file\" and another #include\"$FileArray_Include{uc($file)}\" \n")
    }
  }
  if ($line =~ /^\.file[\s]*[\"\<](.*)[\"\>]/)
  {
    $file = $1;
    if ($FileArray_Include{uc($file)} eq "")
    {
       $FileArray_Include{uc($file)} = "$file";
    }
    elsif ($FileArray_Include{uc($file)} ne "$file")
    {
       print("Warning: difference between .file\"$file\" and another .file\"$FileArray_Include{uc($file)}\" \n")
    }
  }
}
#=====================================================================================
# 
#=====================================================================================


foreach my $file_name (sort keys %FileArray_List) 
{
   if ($FileArray_Dir{$file_name} ne $FileArray_Include{$file_name})
   {
       if ($FileArray_Include{$file_name} ne "")
       {
          if ($FileArray_Dir{$file_name} eq "")
          {
       
             print("Warning: source file \"$FileArray_Include{$file_name}\" is not present\n")
          }
          else
          {
             print("Warning: difference between #include or .file \"$FileArray_Include{$file_name}\" and source file name \"$FileArray_Dir{$file_name}\" \n")
          }
       }
   }
}

#=====================================================================================
# 
#=====================================================================================

