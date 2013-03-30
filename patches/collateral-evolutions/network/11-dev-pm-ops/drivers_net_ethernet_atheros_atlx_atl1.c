--- a/drivers/net/ethernet/atheros/atlx/atl1.c
+++ b/drivers/net/ethernet/atheros/atlx/atl1.c
@@ -2877,6 +2877,9 @@
 	return 0;
 }
 
+compat_pci_suspend(atl1_suspend)
+compat_pci_resume(atl1_resume)
+
 static SIMPLE_DEV_PM_OPS(atl1_pm_ops, atl1_suspend, atl1_resume);
 #define ATL1_PM_OPS	(&atl1_pm_ops)
 
@@ -3147,7 +3150,12 @@
 	.probe = atl1_probe,
 	.remove = atl1_remove,
 	.shutdown = atl1_shutdown,
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,29))
 	.driver.pm = ATL1_PM_OPS,
+#elif defined(CONFIG_PM_SLEEP)
+	.suspend        = atl1_suspend_compat,
+	.resume         = atl1_resume_compat,
+#endif
 };
 
 /**