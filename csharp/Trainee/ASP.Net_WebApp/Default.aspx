<%@ Page Language="C#" AutoEventWireup="true" CodeFile="Default.aspx.cs" Inherits="ScrollProxy._Default" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
    <title>Untitled Page</title>
    <link href="resources/css/ext-all.css" rel="stylesheet" type="text/css" />

    <script src="scripts/extjs/ext-base.js" type="text/javascript"></script>

    <script src="scripts/extjs/ext-all-debug.js" type="text/javascript"></script>

</head>
<body>
    <form runat="server">
        <asp:ScriptManager ID="ScriptManager1" EnablePageMethods="true" runat="server">
            <Scripts>
                <asp:ScriptReference Path = "scripts/extjs/OnInit.js" />
            </Scripts>
        </asp:ScriptManager>
    </form>
    <div id="grid_sample"></div>
</body>
</html>
