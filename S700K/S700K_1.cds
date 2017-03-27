<distribution version="8.1.0" name="S700K" type="MSI">
	<msi GUID="{14AB96FC-D5C8-4823-B6DA-073BE5E34A52}">
		<general appName="S700K" outputLocation="e:\Project_S700K\S700K\cvidistkit.S700K_1" relOutputLocation="cvidistkit.S700K_1" outputLocationWithVars="e:\Project_S700K\S700K\cvidistkit.%name_1" relOutputLocationWithVars="cvidistkit.%name_1" autoIncrement="true" version="1.0.2">
			<arp company="西安齐力铁路电气有限公司" companyURL="" supportURL="" contact="" phone="" comments=""/>
			<summary title="" subject="" keyWords="" comments="" author=""/></general>
		<userinterface language="English" readMe="" license=""><dlgstrings welcomeTitle="S700K" welcomeText="">
			</dlgstrings></userinterface>
		<dirs appDirID="100">
			<installDir name="[Program Files]" dirID="2" parentID="-1" isMSIDir="true" visible="true"/>
			<installDir name="S700K" dirID="100" parentID="2" isMSIDir="false" visible="true"/>
			<installDir name="[Start&gt;&gt;Programs]" dirID="7" parentID="-1" isMSIDir="true" visible="true"/>
			<installDir name="S700K" dirID="101" parentID="7" isMSIDir="false" visible="true"/></dirs>
		<files>
			<simpleFile fileID="0" sourcePath="e:\Project_S700K\S700K\S700K.exe" targetDir="100" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="1" sourcePath="C:\WINDOWS\system32\WS2_32.dll" targetDir="100" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/></files>
		<fileGroups>
			<projectOutput targetType="0" dirID="100" projectID="0">
				<fileID>0</fileID></projectOutput>
			<projectDependencies dirID="100" projectID="0">
				<fileID>1</fileID></projectDependencies></fileGroups>
		<shortcuts>
			<shortcut name="S700K" targetFileID="0" destDirID="101" cmdLineArgs="" description="" runStyle="NORMAL"/></shortcuts>
		<mergemodules/>
		<products/>
		<runtimeEngine cvirte="true" instrsup="true" lvrt="true" analysis="true" netvarsup="true" dotnetsup="true" activeXsup="true" lowlevelsup="true" installToAppDir="false"/>
		<advanced mediaSize="650">
			<launchConditions>
				<condition>MINOS_WIN2K_SP3</condition>
			</launchConditions>
			<includeConfigProducts>true</includeConfigProducts>
			<maxImportVisible>silent</maxImportVisible>
			<maxImportMode>merge</maxImportMode></advanced>
		<Projects NumProjects="1">
			<Project000 ProjectID="0" ProjectAbsolutePath="e:\Project_S700K\S700K\S700K.prj" ProjectRelativePath="S700K.prj"/></Projects>
		<buildData progressBarRate="0.044339094610865">
			<progressTimes>
					<Begin>0.000000000000000</Begin>
					<ProductsAdded>0.030999660491943</ProductsAdded>
					<DPConfigured>0.703000068664551</DPConfigured>
					<DPMergeModulesAdded>2.000000000000000</DPMergeModulesAdded>
					<DPClosed>4.358999729156494</DPClosed>
					<DistributionsCopied>4.375000000000000</DistributionsCopied>
					<End>22.553460073471072</End></progressTimes></buildData>
	</msi>
</distribution>
