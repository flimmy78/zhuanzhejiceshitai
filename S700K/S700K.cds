<distribution version="13.0.2" name="S700K" type="MSI">
	<prebuild>
		<workingdir>workspacedir</workingdir>
		<actions></actions></prebuild>
	<postbuild>
		<workingdir>workspacedir</workingdir>
		<actions></actions></postbuild>
	<msi GUID="{CA8CC688-3749-4BC1-9AA4-A2DDA635C780}">
		<general appName="S700K" outputLocation="d:\document\zhangpei\working\转辙机测试台\working\S700K\cvidistkit.S700K" relOutputLocation="cvidistkit.S700K" outputLocationWithVars="d:\document\zhangpei\working\转辙机测试台\working\S700K\cvidistkit.%name" relOutputLocationWithVars="cvidistkit.%name" upgradeBehavior="1" autoIncrement="true" version="1.0.2">
			<arp company="西安齐力铁路电气有限公司" companyURL="" supportURL="" contact="" phone="" comments="唐波编写"/>
			<summary title="" subject="" keyWords="" comments="" author=""/></general>
		<userinterface language="Chinese (Simplified)" showPaths="true" readMe="" license="">
			<dlgstrings welcomeTitle="西门子转辙机测试台------上位机控制程序" welcomeText=""/></userinterface>
		<dirs appDirID="100">
			<installDir name="[Program Files]" dirID="2" parentID="-1" isMSIDir="true" visible="true" unlock="false"/>
			<installDir name="西门子转辙机测试台" dirID="100" parentID="2" isMSIDir="false" visible="true" unlock="false"/>
			<installDir name="New Folder" dirID="101" parentID="100" isMSIDir="false" visible="true" unlock="false"/>
			<installDir name="[Start&gt;&gt;Programs]" dirID="7" parentID="-1" isMSIDir="true" visible="true" unlock="false"/>
			<installDir name="S700K" dirID="102" parentID="7" isMSIDir="false" visible="true" unlock="false"/></dirs>
		<files>
			<simpleFile fileID="0" sourcePath="D:\document\zhangpei\working\转辙机测试台\working\S700K\S700KDLL.dll" targetDir="101" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="1" sourcePath="d:\document\zhangpei\working\转辙机测试台\working\S700K\cvibuild.S700K\Release\转辙机测试台.exe" targetDir="101" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="2" sourcePath="d:\document\zhangpei\working\转辙机测试台\working\S700K\cvibuild.S700K\Release\转辙机测试台.exe" targetDir="100" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/></files>
		<fileGroups>
			<projectOutput targetType="0" dirID="101" projectID="0">
				<fileID>1</fileID></projectOutput>
			<projectOutput targetType="0" dirID="100" projectID="0">
				<fileID>2</fileID></projectOutput>
			<projectDependencies dirID="100" projectID="0"/>
			<projectDependencies dirID="101" projectID="0"/></fileGroups>
		<shortcuts>
			<shortcut name="S700K" targetFileID="2" destDirID="102" cmdLineArgs="" description="" runStyle="NORMAL"/></shortcuts>
		<mergemodules/>
		<products>
			<product name="NI LabWindows/CVI Shared Run-Time Engine" UC="{80D3D303-75B9-4607-9312-E5FC68E5BFD2}" productID="{D3C549FD-7DA5-440B-A1BC-DD92C898949A}" path="C:\ProgramData\National Instruments\MDF\ProductCache\" flavorID="_full_" flavorName="Full" verRestr="false" coreVer="">
				<cutSoftDeps/></product></products>
		<nonAutoSelectProducts>
			<productID>{D3C549FD-7DA5-440B-A1BC-DD92C898949A}</productID></nonAutoSelectProducts>
		<runtimeEngine installToAppDir="false" activeXsup="true" analysis="true" cvirte="true" dotnetsup="true" instrsup="true" lowlevelsup="true" lvrt="true" netvarsup="true" rtutilsup="true">
			<hasSoftDeps/>
			<doNotAutoSelect>
			<component>instrsup</component>
			<component>lvrt</component>
			</doNotAutoSelect></runtimeEngine><sxsRuntimeEngine>
			<selected>false</selected>
			<doNotAutoSelect>false</doNotAutoSelect></sxsRuntimeEngine>
		<advanced mediaSize="650">
			<launchConditions>
				<condition>MINOS_WINXP</condition>
			</launchConditions>
			<includeConfigProducts>true</includeConfigProducts>
			<maxImportVisible>silent</maxImportVisible>
			<maxImportMode>merge</maxImportMode>
			<custMsgFlag>false</custMsgFlag>
			<custMsgPath>msgrte.txt</custMsgPath>
			<signExe>false</signExe>
			<certificate></certificate>
			<signTimeURL></signTimeURL>
			<signDescURL></signDescURL></advanced>
		<Projects NumProjects="1">
			<Project000 ProjectID="0" ProjectAbsolutePath="d:\document\zhangpei\working\转辙机测试台\working\S700K\S700K.prj" ProjectRelativePath="S700K.prj"/></Projects>
		<buildData progressBarRate="1.419290606195199">
			<progressTimes>
				<Begin>0.000000000000000</Begin>
				<ProductsAdded>0.135723250000009</ProductsAdded>
				<DPConfigured>0.623238749999970</DPConfigured>
				<DPMergeModulesAdded>2.163223249999987</DPMergeModulesAdded>
				<DPClosed>6.513223500000009</DPClosed>
				<DistributionsCopied>8.863417249999962</DistributionsCopied>
				<End>70.457733999999945</End></progressTimes></buildData>
	</msi>
</distribution>
